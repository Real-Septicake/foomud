#include "mud.hpp"
#include <connection.hpp>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>

Connection::Connection(int sock, int port, std::string addr) :
    sock(sock), port(port), addr(addr)
{

}

Connection::~Connection() {
    if(checkConnection()) {
        std::cout << "Closing socket: " << sock << std::endl;
        Mud::instance().closeConnection(sock);
    }
}

bool Connection::checkConnection() {
    return Mud::instance().checkConnection(sock);
}

void Connection::read() {
    char buf[1024];
    if(closing)
        return;

    ssize_t nread = recv(sock, &buf, 1023, MSG_DONTWAIT);
    if(nread <= 0) {
        perror("Read");
        Mud::instance().closeConnection(sock);
        sock = -1;
        return;
    }

    std::size_t uread = static_cast<std::size_t>(nread);
    ibuf = std::string(buf, uread);
    ibuf[uread] = 0;
    std::cout << ibuf << std::endl;
}

void Connection::write() {
}
