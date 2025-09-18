#include "asio/buffer.hpp"
#include "asio/completion_condition.hpp"
#include "asio/error.hpp"
#include "asio/ip/tcp.hpp"
#include "asio/read_until.hpp"
#include "asio/write.hpp"
#include "mud.hpp"
#include <connection.hpp>
#include <iostream>
#include <ostream>
#include <utils.hpp>
#include <sys/socket.h>
#include <sys/types.h>

Connection::Connection(asio::ip::tcp::socket s) :
    sock(std::move(s)), ibuf(), obuf(), closed(false)
{
    ibuf.resize(1024);
    read();
}

Connection::~Connection() {
    try {
        sock.close();
        std::cout <<
            (closed ? "Client closed connection" : "Closed socket")
            << std::endl;
    } catch(...) {
        std::cout << "Error closing socket" << std::endl;
    }
}

bool Connection::checkConnection() {
//     return Mud::instance().checkConnection(sock);
     return closed;
}

bool Connection::pendingOutput() {
    return !obuf.empty();
}

void Connection::read() {
    asio::async_read(sock,
            asio::buffer(ibuf, 1024),
            asio::transfer_at_least(1),
            [this](std::error_code e, std::size_t length) {
                if(!e) {
                    std::cout << length << std::endl;
//                     std::cout << ibuf << std::flush;
//                     Mud::instance().broadcast(ibuf);
                    ibuf.clear();
                    ibuf.resize(1024);
                } else if(e == asio::error::eof) {
                    this->closed = true;
                    return;
                } else {
                    this->closed = true;
                    perror("read");
                    return;
                }
loop:
                read();
            }
        );
}

void Connection::write() {
    asio::async_write(sock, 
            asio::buffer(obuf),
            [this](std::error_code e, std::size_t length) {
                if(e) {
                    perror("write");
                }
                obuf.clear();
            }
        );
}
