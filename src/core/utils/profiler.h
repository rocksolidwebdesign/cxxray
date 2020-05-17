#ifndef CXXRAY_PROFILER_H
#define CXXRAY_PROFILER_H

#include <chrono>

namespace CxxRay {

struct Profiler
{
    using ClockT = std::chrono::system_clock;
    using TimePointT = std::chrono::time_point<ClockT>;

    TimePointT mStart;

    Profiler() {
        mStart = ClockT::now();
    }

    void start(void) {
        mStart = ClockT::now();
    }

    double stop(void) {
        using std::chrono::duration_cast;
        using std::chrono::microseconds;

        return static_cast<double>(duration_cast<microseconds>(
            ClockT::now() - mStart
        ).count()) / 1000.0;
    }
};

} // namespace CxxRay

#endif
