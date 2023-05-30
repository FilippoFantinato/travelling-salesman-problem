#ifndef UTILS_MEASURE_TIME_H
#define UTILS_MEASURE_TIME_H

#include <chrono>

using namespace std::chrono;

#define duration(a) std::chrono::duration_cast<std::chrono::seconds>(a).count()
#define time_now() std::chrono::high_resolution_clock::now()

namespace Utils
{
    double measure_time(auto f)
    {
        system_clock::time_point t1 = time_now();
        f();
        return duration(time_now() - t1);
    }
};

#endif
