#include "asio/io_context.hpp"
#include "connection.hpp"
#include "repeating_timer.hpp"
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

static fd_set ifds, ofds, efds;

void sig_handler(int) {
    std::cout << std::endl << "signal recieved" << std::endl;
    Mud::instance().shutdown();
}

Mud::Mud() :
    context(),
    acceptor(context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 4000)),
    running(true)
{
}

Mud::~Mud() {
}

bool Mud::run() {
    signal(SIGTERM, sig_handler);
    signal(SIGINT, sig_handler);

    if(!startConnection()) {
        std::cerr << "Error starting server socket" << std::endl;
        return false;
    }

    std::cout << "starting loop" << std::endl;

    RepeatingTimer timer(context, std::chrono::milliseconds(50));

    timer.start([this](std::error_code) {
            this->removeClosedConnections();
            for(auto c : this->connections)
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

void Mud::processConnection(std::shared_ptr<Connection> c) {
    if(c->pendingInput()) {
        std::cout << c->ibuf.length() << std::endl;
        c->ibuf.clear();
    }
    if(c->pendingOutput()) {
        c->write();
    }
}

bool Mud::checkConnection(const int &sock) {
    int err_code;
    socklen_t err_code_sz = sizeof(err_code);
    return getsockopt(sock, SOL_SOCKET, SO_ERROR, &err_code, &err_code_sz) == 0;
}

void Mud::acceptConnections() {
    acceptor.async_accept(
        [this](std::error_code e, asio::ip::tcp::socket s) {
            if(!e) {
                std::cout << "Addr:" << s.remote_endpoint().address().to_string() <<
                    "|Port:" << s.remote_endpoint().port() << std::endl;
                auto c = std::make_shared<Connection>(std::move(s));
                c->obuf += "Greetings\n";
                this->connections.push_back(c);
            }

            acceptConnections();
        });
     return;
}

bool Mud::closeConnection(const int &sock) {
    return close(sock) == 0;
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
        std::unordered_set<std::shared_ptr<Connection>> remove;
        for(auto c = connections.begin();
                c != connections.end();
                ++c) {
            if((*c)->closed)
                remove.insert(*c);
        }
        for(auto c : remove) {
            std::cout << "Closing [" << c->sock.remote_endpoint().address().to_string() << "]:"
                << c->sock.remote_endpoint().port() << std::endl;
            removeConnection(c);
        }
}

void Mud::removeConnection(std::shared_ptr<Connection> connection) {
    for(auto it = connections.begin(); it != connections.end(); ++it) {
        if(connection == *it) {
            connections.erase(it);
            return;
        }
    }
}

void Mud::broadcast(const std::string &s) {
    for(auto c : connections) {
        c->obuf += s;
    }
}

Mud& Mud::instance() {
    static Mud i;
    return i;
}
