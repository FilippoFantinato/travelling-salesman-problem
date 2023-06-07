#ifndef UTILS_MEASURE_TIME_H
#define UTILS_MEASURE_TIME_H

#include <iostream>
#include <functional>
#include <chrono>

#define duration(a) std::chrono::duration_cast<std::chrono::milliseconds>(a).count()
#define time_now() std::chrono::high_resolution_clock::now()

namespace Utils
{
    double measure_time(const std::function<void(void)>& f);
}

#endif
