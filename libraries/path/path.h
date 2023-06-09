#ifndef TSP_PATH_H
#define TSP_PATH_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <functional>

#include "../tsp/tsp.h"
#include "../utils/math.h"

typedef std::vector<Vertex> Path;

double compute_path_cost(const TSP& tsp, const Path& path);
double compute_tour_cost(const TSP& tsp, const Path& tour);

std::ostream& operator<<(std::ostream& os, const Path& p);

#endif
