#include "asio/buffer.hpp"
#include "asio/read.hpp"
#include <connection.hpp>
#include <iostream>
#include <ostream>
#include <utils.hpp>
#include <sys/socket.h>
#include <sys/types.h>

Connection::Connection(asio::ip::tcp::socket s) :
    sock(std::move(s)), ibuf(), obuf()
{
    read();
}

Connection::~Connection() {
//     if(checkConnection()) {
//         std::cout << "Closing socket: " << sock << std::endl;
//         Mud::instance().closeConnection(sock);
//     }
}

bool Connection::checkConnection() {
//     return Mud::instance().checkConnection(sock);
     return true;
}

bool Connection::pendingOutput() {
    return !obuf.empty();
}

#define BUFSZ 1024

void Connection::read() {
    asio::async_read(sock, 
            asio::buffer(ibuf),
            [this](std::error_code e, std::size_t length) {
                if(!e && length) {
                    std::cout << ibuf << std::endl;
                }

                read();
            }
            );
//     char buf[BUFSZ];
//     if(closing)
//         return;
// 
//     ssize_t nread = recv(sock, &buf, BUFSZ - 1, MSG_DONTWAIT);
//     if(nread <= 0) {
//         perror("Read");
//         Mud::instance().closeConnection(sock);
//         sock = -1;
//         return;
//     }
// 
//     std::size_t uread = static_cast<std::size_t>(nread);
//     ibuf = std::string(buf, uread);
//     ibuf[uread] = 0;
//     std::cout << ibuf << std::endl;
// 
//     obuf += "\0" + ibuf;
}

void Connection::write() {
//     while(sock != -1 && !obuf.empty()) {
//         findReplace(obuf, "\n", "\r\n");
//         std::size_t ilen = std::min<size_t>(obuf.size(), BUFSZ);
// 
//         ssize_t nwrite = send(sock, obuf.c_str(), obuf.size(), MSG_NOSIGNAL);
// 
//         if(nwrite <= 0) {
//             perror("Write");
//             return;
//         }
// 
//         std::size_t uwrite = static_cast<std::size_t>(uwrite);
// 
//         obuf.erase(0, obuf.size());
// 
//         if(uwrite < nwrite) {
//             break;
//         }
//     }
}
