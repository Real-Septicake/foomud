#ifndef REPEATING_TIMER_HPP
#define REPEATING_TIMER_HPP

#include "asio/io_context.hpp"
#include "asio/steady_timer.hpp"
#include <chrono>
class RepeatingTimer {
    typedef std::function<void(std::error_code)> callback;
    public:
        RepeatingTimer(asio::io_context &, std::chrono::milliseconds);
        void start(callback);
    private:
        void init();
        asio::steady_timer timer;
        std::chrono::milliseconds duration;
        callback cb;
};

#endif
