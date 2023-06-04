#include "path.h"

double compute_path_cost(const TSP& tsp, const Path& path)
{
    double cost = 0;

    auto prev = path.cbegin();
    for(auto it = std::next(path.cbegin(), 1); it != path.cend(); ++it)
    {
        cost += tsp.get_weight(*prev, *it);
        prev = it;
    }

    return cost;
}

double compute_tour_cost(const TSP& tsp, const Path& tour)
{
    return compute_path_cost(tsp, tour)
            + tsp.get_weight(*tour.rbegin(), *(tour.begin()));
}