#include "measure-time.h"

using namespace std::chrono;

namespace Utils
{
    double measure_time(const std::function<void(void)>& f)
    {
        system_clock::time_point t1 = time_now();
        f();
        return duration(time_now() - t1) / 1000.0;
    }
}