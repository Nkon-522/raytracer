#ifndef RAYTRACER_TIMER_H
#define RAYTRACER_TIMER_H

#include <chrono>

class Timer {
public:
    void start() {
        m_StartTime = std::chrono::system_clock::now();
        m_bRunning = true;
    }

    void stop() {
        m_EndTime = std::chrono::system_clock::now();
        m_bRunning = false;
    }

    [[nodiscard]] double elapsedMilliseconds() const {
        std::chrono::time_point<std::chrono::system_clock> endTime;

        if(m_bRunning) {
            endTime = std::chrono::system_clock::now();
        }
        else {
            endTime = m_EndTime;
        }

        return static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>((endTime - m_StartTime)).count());
    }

    [[maybe_unused]] [[nodiscard]] double elapsedSeconds() const {
        return elapsedMilliseconds() / 1000.0;
    }

private:
    std::chrono::time_point<std::chrono::system_clock> m_StartTime;
    std::chrono::time_point<std::chrono::system_clock> m_EndTime;
    bool                                               m_bRunning = false;
};

#endif //RAYTRACER_TIMER_H
