#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <string>

class Connection {
    private:
        std::string ibuf;
        std::string obuf;
    public:
        int sock;
        int port;
        std::string addr;
        bool closing;
        ~Connection();
        Connection(int sock, int port, std::string addr);
        bool checkConnection();
        void read();
        void write();
};


#endif
