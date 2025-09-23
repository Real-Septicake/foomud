#include "asio/io_context.hpp"
#include "characters/player.hpp"
#include "command/command.hpp"
#include "connection.hpp"
#include "input/handlers/handler.hpp"
#include "input/handlers/name.hpp"
#include "repeating_timer.hpp"
#include "utils.hpp"
#include <asm-generic/socket.h>
#include <cerrno>
#include <chrono>
#include <csignal>
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
    running(true), rooms()
{
    rooms.insert({0, std::make_shared<Room>()});
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

    std::cout << "starting loop" << std::endl;

    RepeatingTimer timer(context, std::chrono::milliseconds(50));

    timer.start([this](std::error_code) {
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
                p->sendMsg("Greetings\n");
                players.push_back(p);
                auto r = rooms.find(0);
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
    for(auto it = players.begin(); it != players.end(); ++it) {
        if(connection == *it) {
            connection->current_room->remCharacter(connection->shared_from_this());
            players.erase(it);
            return;
        }
    }
}

void Mud::broadcast(const std::string &s) {
    for(auto p : players) {
        p->c->obuf += s;
    }
}

void Mud::handleInput(std::string &s, std::shared_ptr<Player> p) {
}

Mud& Mud::instance() {
    static Mud i;
    return i;
}
