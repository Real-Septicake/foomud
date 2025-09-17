#include <repeating_timer.hpp>

RepeatingTimer::RepeatingTimer(asio::io_context &c, std::chrono::milliseconds duration) :
    timer(c, duration), duration(duration)
{
}

void RepeatingTimer::start(const callback cb) {
    this->cb = cb;
    init();
}

void RepeatingTimer::stop() {
    running = false;
}

void RepeatingTimer::init() {
    timer.async_wait([this](std::error_code e)
            {
                cb(e);
                timer.expires_at(timer.expiry() + duration);
                if(running)
                    init();
            }
        );
}
