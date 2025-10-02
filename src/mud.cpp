#include "asio/io_context.hpp"
#include "characters/player.hpp"
#include "command/command.hpp"
#include "connection.hpp"
#include "input/handlers/handler.hpp"
#include "input/handlers/name.hpp"
#include "repeating_timer.hpp"
#include "structure/exit.hpp"
#include "transport/train.hpp"
#include "updater/updater.hpp"
#include <asm-generic/socket.h>
#include <cerrno>
#include <chrono>
#include <csignal>
#include <cstddef>
#include <cstdio>
#include <exception>
#include <memory>
#include <mud.hpp>
#include <iostream>
#include <sys/select.h>
#include <sys/socket.h>
#include <system_error>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unordered_set>
#include <structure/room.hpp>

void sig_handler(int) {
    std::cout << std::endl << "signal recieved" << std::endl;
    Mud::instance().shutdown();
}

Mud::Mud() :
    context(),
    acceptor(context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 4000)),
    max_room_vnum(), max_item_vnum(), running(true), rooms()
{
}

Mud::~Mud() {
}

bool Mud::addCommand(std::shared_ptr<Command> c) {
    return commands.insert({c->name, c}).second;
}

bool Mud::run() {
    signal(SIGTERM, sig_handler);
    signal(SIGINT, sig_handler);

    if(!startConnection()) {
        std::cerr << "Error starting server socket" << std::endl;
        return false;
    }

    loadCommands();

    auto r0 = std::make_shared<Room>();
    addRoom(r0);
    auto r1 = std::make_shared<Room>();
    addRoom(r1);
    r0->addExit(r1, Direction::East);
    r1->addExit(r0, Direction::West);
    r1->addExit(r1, Direction::Down);

    auto i = std::make_shared<Item>();
    i->name = "ITEM!!!!";
    i->article = Article::Vowel;
    addItem(i);
    r1->addItem(i);

    auto r = std::make_shared<Room>();
    addRoom(r);
    auto t = std::make_shared<Train>();
    addTrans(t->shared_from_this());
    t->internal_room = r;

    auto s1 = std::make_shared<Stop>(10, r0);
    addStop(s1);
    auto s2 = std::make_shared<Stop>(0, r1);
    addStop(s2);
    s2->prev = s1;
    s1->next = s2;

    t->stop = s1;

    t->internal_room->addExit(r0, Direction::Out);
    r0->addExit(t->internal_room, Direction::In);

    std::cout << "starting loop" << std::endl;

    RepeatingTimer timer(context, std::chrono::milliseconds(50));

    timer.start([this](std::error_code) {
            Updater::instance().update();
            this->removeClosedConnections();
            for(auto c : this->players)
                this->processConnection(c);
        });

    acceptConnections();

    context.run();

    endConnection();

    return true;
}

void Mud::shutdown() {
    std::cout << "Shutdown called" << std::endl;
    context.stop();
}

bool Mud::startConnection() {
    try {
        acceptor.listen();
    } catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }

    return true;
}

void Mud::processConnection(std::shared_ptr<Player> p) {
    if(p->c->pendingOutput()) {
        p->c->write();
    }
}

void Mud::acceptConnections() {
    acceptor.async_accept(
        [this](std::error_code e, asio::ip::tcp::socket s) {
            if(!e) {
                std::cout << "Addr:" << s.remote_endpoint().address().to_string() <<
                    "|Port:" << s.remote_endpoint().port() << std::endl;
                auto c = std::make_unique<Connection>(std::move(s));
                std::shared_ptr<Player> p = std::make_shared<Player>();
                p->init(std::move(c));
                p->handler = std::static_pointer_cast<Handler>(std::make_shared<NameHandler>());
                p->sendMsg("Greetings\r\nName: ");
                players.insert(p);
                auto r = rooms.find(1);
                if(r != rooms.end())
                    r->second->addCharacter(p);
            }

            acceptConnections();
        });
     return;
}

void Mud::closeConnection(std::shared_ptr<Player> p) {
    try { p->c->sock.close(); }
    catch (...) {}
}

bool Mud::endConnection() {
    try {
        std::cout << "ending" << std::endl;
        acceptor.close();
        return true;
    } catch(...) {
        return false;
    }
}

void Mud::removeClosedConnections() {
        std::unordered_set<std::shared_ptr<Player>> remove;
        for(auto p = players.begin();
                p != players.end();
                ++p) {
            if((*p)->c->closed)
                remove.insert(*p);
        }
        for(auto p : remove) {
            try {
            std::cout << "Closing [" << p->c->sock.remote_endpoint().address().to_string() << "]:"
                << p->c->sock.remote_endpoint().port() << std::endl;
            } catch(...) {
                std::cout << "unknown]" << std::endl;
            }
            removeConnection(p);
            p.reset();
        }
}

void Mud::removeConnection(std::shared_ptr<Player> connection) {
    connection->current_room->remCharacter(connection->shared_from_this());
    players.erase(connection);
    return;
}

void Mud::broadcast(const std::string &s) {
    for(auto p : players) {
        p->c->obuf += s;
    }
}

Mud& Mud::instance() {
    static Mud i;
    return i;
}

std::size_t Mud::maxRoomVnum() const {
    return max_room_vnum;
}

std::size_t Mud::maxItemVnum() const {
    return max_item_vnum;
}

std::size_t Mud::maxStopVnum() const {
    return max_stop_vnum;
}

std::size_t Mud::maxTransVnum() const {
    return max_trans_vnum;
}

bool Mud::addRoom(std::shared_ptr<Room> room) {
    bool r = rooms.insert({room->vnum, room}).second;
    if(r)
        max_room_vnum = std::max(max_room_vnum, room->vnum);
    return r;
}

bool Mud::addItem(std::shared_ptr<Item> item) {
    bool r = items.insert({item->vnum, item}).second;
    if(r)
        max_item_vnum = std::max(max_item_vnum, item->vnum);
    return r;
}

bool Mud::addStop(std::shared_ptr<Stop> stop) {
    bool r = stops.insert({stop->vnum, stop}).second;
    if(r)
        max_stop_vnum = std::max(max_stop_vnum, stop->vnum);
    return r;
}

bool Mud::addTrans(std::shared_ptr<Transport> trans) {
    bool r = transes.insert({trans->vnum, trans}).second;
    if(r)
        max_stop_vnum = std::max(max_stop_vnum, trans->vnum);
    return r;
}
