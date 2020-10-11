#include "core/Timer.hpp"

namespace celadon {

    void Timer::start() {
        m_start = clock_.now();
    }
    void Timer::end() {
        m_end = clock_.now();
    }

    double Timer::elapsed() {
        return std::chrono::duration_cast<std::chrono::duration<double>>(m_end - m_start).count();
    }   
}