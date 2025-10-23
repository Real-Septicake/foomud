#include "asio/buffer.hpp"
#include "asio/completion_condition.hpp"
#include "asio/error.hpp"
#include "asio/ip/tcp.hpp"
#include "asio/read.hpp"
#include "asio/write.hpp"
#include "mud.hpp"
#include "print/engine.hpp"
#include <connection.hpp>
#include <iostream>

const FormatEngine<const std::nullptr_t> Connection::engine{{
    {'u', [](auto){ return "\x1b[4m"; }},
    {'U', [](auto){ return "\x1b[24m"; }},
    {'r', [](auto){ return "\x1b[m"; }},
    {'R', [](auto){ return "\x1b[m"; }}
}, false, nullptr, '^'};

Connection::Connection(asio::ip::tcp::socket s) :
    ibuf(), obuf(), sock(std::move(s)), closed(false)
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
            [this](std::error_code e, std::size_t /*length*/) {
                if(!e) {
                    parent.lock()->handler->process(parent.lock(), ibuf);
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
    obuf += "^r"; // guarantee that any dangling attributes are cleared
    std::string o = engine.fmt(nullptr, obuf);
    asio::async_write(sock, 
            asio::buffer(o),
            [this](std::error_code e, std::size_t /*length*/) {
                if(e) {
                    perror("write");
                }
                obuf.clear();
            }
        );
}
