#ifndef SOLUTION_H
#define SOLUTION_H

#include <utility>

#include "../libraries/path/path.h"

struct Solution {
    std::shared_ptr<const Path> path;
    const double cost;
    const double time;

    Solution(std::shared_ptr<const Path> path, double cost, double time)
        : path(std::move(path)), cost(cost), time(time) {}
};

#endif
