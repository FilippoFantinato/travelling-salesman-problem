#include "./math.h"

namespace Math
{
    double round(double n, int decimal)
    {
        int inc = 1;
        for(int i = 0; i < decimal; ++i)
        {
            inc *= 10;
        }

        return std::round(n * inc) / inc;
    }

    double relative_error(double approx, double optimal)
    {
        return (approx - optimal) / optimal;
    }
}
