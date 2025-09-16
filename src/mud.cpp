#include "connection.hpp"
#include <asm-generic/socket.h>
#include <cerrno>
#include <csignal>
#include <cstdio>
#include <mud.hpp>
#include <iostream>
#include <set>
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
    serv_sock(-1),
    max_socks(-1),
    running(true),
    port(4001)
{

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
    timeout.tv_usec = 250000;

    do {
        FD_ZERO(&ifds);
        FD_ZERO(&ofds);
        FD_ZERO(&efds);

        FD_SET(serv_sock, &ifds);

        for(auto c : connections) {
            if(c->checkConnection()) {
                max_sock = std::max(max_sock, c->sock);
                FD_SET(c->sock, &ifds);
                FD_SET(c->sock, &efds);
                // if pending output, set ofds
            }
        }

        int activity = select(max_sock + 1, &ifds, &ofds, &efds, &timeout);
        if(activity < 0 && errno != EINTR) {
            perror("Select");
        }

        if(FD_ISSET(serv_sock, &ifds)) {
            std::cout << "Accepting" << std::endl;
            if(!acceptConnections()) {
                std::cerr << "Connection's fucked" << std::endl;
            }
        }

        for(auto c : connections) {
            processConnection(c);
        }

        removeClosedConnections();
    } while(running);
    endConnection();
    return true;
}

void Mud::shutdown() {
    std::cout << "Shutdown called" << std::endl;
    running = false;
}

bool Mud::startConnection() {
    struct sockaddr_in sock_addr;
    if((serv_sock = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Creating Server Socket");
        return false;
    }

    if(fcntl(serv_sock, F_SETFL, FNDELAY) == -1) {
        perror("Server Socket FCNTL");
        return false;
    }

    struct linger l = linger();
    if(setsockopt(serv_sock, SOL_SOCKET, SO_LINGER, (char *)&l, sizeof(l)) < 0) {
        perror("Linger");
        return false;
    }

    int x = 1;
    if(setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, (char *)&x, sizeof(x)) == -1) {
        perror("Reuse");
        return false;
    }

    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(port);
    sock_addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(serv_sock, (struct sockaddr *)&sock_addr, sizeof(sockaddr)) < 0) {
        perror("Bind");
        return false;
    }

    if(listen(serv_sock, SOMAXCONN) == -1) {
        perror("Listen");
        return false;
    }

    return true;
}

void Mud::processConnection(Connection *c) {
    if(c->checkConnection()) {
        if(FD_ISSET(c->sock, &efds)) {
        }
    }
    if(c->checkConnection()) {
        if(FD_ISSET(c->sock, &ifds)) {
            c->read();
        }
    }
    if(c->checkConnection()) {
        if(FD_ISSET(c->sock, &ofds)) {
        }
    }
}

bool Mud::checkConnection(const int &sock) {
    int err_code;
    socklen_t err_code_sz = sizeof(err_code);
    return getsockopt(sock, SOL_SOCKET, SO_ERROR, &err_code, &err_code_sz) == 0;
}

bool Mud::acceptConnections() {
    int incoming_sock;
    struct sockaddr_in incoming_addr;
    socklen_t addr_sz = sizeof(incoming_addr);

    while(true) {
        incoming_sock = accept(serv_sock, (struct sockaddr *)&incoming_addr, &addr_sz);
        if(incoming_sock == -1) {
            if(errno == EWOULDBLOCK) {
                break;
            }
            perror("Accept");
            return false;
        }

        if(fcntl(incoming_sock, F_SETFL, FNDELAY) == -1) {
            perror("Incoming Socket FCNTL");
            return false;
        }

        std::cout << "Addr:" << inet_ntoa(incoming_addr.sin_addr)
            << "|Port:" << incoming_addr.sin_port
            << "|FD:" << incoming_sock << std::endl;
        connections.push_back(new Connection(incoming_sock, incoming_addr.sin_port, inet_ntoa(incoming_addr.sin_addr)));
    }
    return true;
}

bool Mud::closeConnection(const int &sock) {
    return close(sock) == 0;
}

bool Mud::endConnection() {
    return (serv_sock == -1) ? false : this->closeConnection(serv_sock);
}

void Mud::removeClosedConnections() {
    std::set<Connection *> remove;
    for(auto c : connections) {
        if(!c->checkConnection()) {
            remove.insert(c);
        }
    }

    for(auto it = remove.begin(); it != remove.end(); it++) {
        auto connection = *it;
        std::cout << "Removing connection: " << connection->addr << std::endl;
        removeConnection(connection);
        delete connection;
    }
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
