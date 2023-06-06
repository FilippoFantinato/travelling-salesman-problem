#ifndef UTILS_RANDOM_H
#define UTILS_RANDOM_H

#include <vector>
#include <random>

namespace Utils
{
    template<class V>
    const V& choice(const std::vector<V> choices, const std::vector<double>& weights)
    {
        std::random_device rd;
        std::discrete_distribution<> dist(weights.begin(), weights.end());
        std::mt19937 gen(rd());

        return choices[dist(gen)];
    }
}

#endif
