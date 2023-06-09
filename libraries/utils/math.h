#ifndef TSP_UTILS_MATH_H
#define TSP_UTILS_MATH_H

#include <vector>
#include <cmath>

namespace Math {

    template<class T>
    double std_dev(const std::vector<T>& xs, double mean)
    {
        double s = 0;
        for(const auto& x: xs)
        {
            s += pow(x - mean, 2);
        }

        return sqrt(s / xs.size());
    }

    double round(double n, int decimal);
}

#endif
