#ifndef MUD_HPP
#define MUD_HPP

#include <vector>
#include <connection.hpp>

class Mud {
    private:
        int serv_sock;
        int max_socks;
        long port;
        bool running;
        int max_sock;
        std::vector<Connection *> connections;
        Mud();
        ~Mud();
    public:
        bool run();
        void shutdown();
        bool startConnection();
        bool acceptConnections();
        void processConnection(Connection *);
        bool checkConnection(const int &);
        bool closeConnection(const int &);
        bool endConnection();
        void removeClosedConnections();
        void removeConnection(Connection *);
        static Mud& instance();
};

#endif
