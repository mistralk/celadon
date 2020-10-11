#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

namespace celadon {
    class Timer {
    private:
        std::chrono::high_resolution_clock clock_;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_end;

    public:
        Timer() = default;
        ~Timer() = default;

        void start();
        void end();
        double elapsed();
    };
}

#endif