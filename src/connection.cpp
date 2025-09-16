#include "asio/buffer.hpp"
#include "asio/error.hpp"
#include "asio/read_until.hpp"
#include "asio/write.hpp"
#include <connection.hpp>
#include <iostream>
#include <ostream>
#include <utils.hpp>
#include <sys/socket.h>
#include <sys/types.h>

Connection::Connection(asio::ip::tcp::socket s) :
    sock(std::move(s)), ibuf(), obuf()
{
    ibuf.resize(1024);
    read();
}

Connection::~Connection() {
    try {
        sock.close();
        std::cout << "Closed socket" << std::endl;
    } catch(...) {
        std::cout << "Socket already closed" << std::endl;
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
    asio::async_read_until(sock, 
            asio::dynamic_buffer(ibuf), '\n',
            [this](std::error_code e, std::size_t length) {
                if(!e) {
                    std::cout << ibuf << std::flush;
                    ibuf.clear();
                    obuf = "written\n";
                    write();
                } else if(e == asio::error::eof) {
                    std::cout << "closed" << std::endl;
                    this->closed = true;
                    return;
                } else {
                    perror("write");
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
