#include "asio/error.hpp"
#include "asio/error_code.hpp"
#include "asio/io_context.hpp"
#include "connection.hpp"
#include <asm-generic/socket.h>
#include <cerrno>
#include <csignal>
#include <cstdio>
#include <exception>
#include <mud.hpp>
#include <iostream>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/ioctl.h>

static fd_set ifds, ofds, efds;

void sig_handler(int) {
    std::cout << std::endl << "damn" << std::endl;
    Mud::instance().shutdown();
}

Mud::Mud() :
    context(),
    acceptor(context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 4000)),
    running(true)
{
    acceptor.non_blocking(true);
}

Mud::~Mud() {
    for(auto c : connections) {
        delete c;
    }
}

bool Mud::run() {
    signal(SIGTERM, sig_handler);
    signal(SIGINT, sig_handler);

    if(!startConnection()) {
        std::cerr << "Error starting server socket" << std::endl;
        return false;
    }

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 500000;
    std::cout << "starting loop" << std::endl;

    while(running) {
        acceptConnections();
    }
    endConnection();

    return true;

//     do {
//         int activity = select(max_sock + 1, &ifds, &ofds, &efds, &timeout);
//         if(activity < 0 && errno != EINTR) {
//             perror("Select");
//         }
// 
//         if(acceptor.non_blocking()
// 
//         for(auto c : connections) {
//             processConnection(c);
//         }
// 
//         removeClosedConnections();
//     } while(running);
//     endConnection();
//     return true;
}

void Mud::shutdown() {
    std::cout << "Shutdown called" << std::endl;
    running = false;
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

void Mud::processConnection(Connection *c) {
}

bool Mud::checkConnection(const int &sock) {
    int err_code;
    socklen_t err_code_sz = sizeof(err_code);
    return getsockopt(sock, SOL_SOCKET, SO_ERROR, &err_code, &err_code_sz) == 0;
}

bool Mud::acceptConnections() {
    while(true) {
        asio::ip::tcp::socket s = asio::ip::tcp::socket(context);
        asio::error_code e;
        auto _ = acceptor.accept(s, e);
        if(e) {
            if(e == asio::error::would_block) {
                break;
            }
            perror("Accept");
            return false;
        }

        s.non_blocking(true);

        std::cout << "Addr:" << s.remote_endpoint().address().to_string() <<
            "|Port:" << s.remote_endpoint().port() << std::endl;

        connections.push_back(new Connection(std::move(s)));
    }
    return true;
//     int incoming_sock;
//     struct sockaddr_in incoming_addr;
//     socklen_t addr_sz = sizeof(incoming_addr);
// 
//     while(true) {
//         incoming_sock = accept(serv_sock, (struct sockaddr *)&incoming_addr, &addr_sz);
//         if(incoming_sock == -1) {
//             if(errno == EWOULDBLOCK) {
//                 break;
//             }
//             perror("Accept");
//             return false;
//         }
// 
//         if(fcntl(incoming_sock, F_SETFL, FNDELAY) == -1) {
//             perror("Incoming Socket FCNTL");
//             return false;
//         }
// 
//         std::cout << "Addr:" << inet_ntoa(incoming_addr.sin_addr)
//             << "|Port:" << incoming_addr.sin_port
//             << "|FD:" << incoming_sock << std::endl;
//         connections.push_back(new Connection(incoming_sock, incoming_addr.sin_port, inet_ntoa(incoming_addr.sin_addr)));
//     }
     return true;
}

bool Mud::closeConnection(const int &sock) {
    return close(sock) == 0;
}

bool Mud::endConnection() {
    try {
        acceptor.close();
        return true;
    } catch(...) {
        return false;
    }
}

void Mud::removeClosedConnections() {
//     std::set<Connection *> remove;
//     for(auto c : connections) {
//         if(!c->checkConnection()) {
//             remove.insert(c);
//         }
//     }
// 
//     for(auto it = remove.begin(); it != remove.end(); it++) {
//         auto connection = *it;
//         std::cout << "Removing connection: " << connection->addr << std::endl;
//         removeConnection(connection);
//         delete connection;
//     }
}

void Mud::removeConnection(Connection *connection) {
    for(auto it = connections.begin(); it != connections.end(); it++) {
        if(connection == *it) {
            connections.erase(it);
            return;
        }
    }
}

Mud& Mud::instance() {
    static Mud i;
    return i;
}
