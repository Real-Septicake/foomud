#include "asio/buffer.hpp"
#include "asio/completion_condition.hpp"
#include "asio/error.hpp"
#include "asio/ip/tcp.hpp"
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
     return !closed;
}

bool Connection::pendingOutput() {
    return !obuf.empty();
}

void Connection::read() {
    asio::async_read(sock,
            asio::dynamic_buffer(ibuf),
            asio::transfer_at_least(1),
            [this](std::error_code e, std::size_t length) {
                if(!e) {
                    Mud::instance().handleInput(ibuf, parent.lock());
                    ibuf.clear();
                } else if(e == asio::error::eof) {
                    this->closed = true;
                    return;
                } else {
                    this->closed = true;
                    perror("read");
                    Mud::instance().closeConnection(parent.lock());
                    return;
                }
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
