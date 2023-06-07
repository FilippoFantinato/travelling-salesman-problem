#ifndef INITIALIZERS_H
#define INITIALIZERS_H

#include <memory>

#include "../libraries/tsp/tsp.h"

#include "../libraries/tsp-solvers/TSPSolver.h"
#include "../ant-colony-optimization/ACO.h"
#include "../ant-colony-system/ACS.h"
#include "../gavish-graves/GavishGraves.h"
#include "../nearest-neighbour/NearestNeighbour.h"

namespace Init
{
    using InitSolver = std::function<std::unique_ptr<TSPSolver>(const TSP&)>;

    std::unique_ptr<TSPSolver> init_ant_colony_optimization(const TSP& tsp);
    std::unique_ptr<TSPSolver> init_ant_colony_system(const TSP& tsp);
    std::unique_ptr<TSPSolver> init_gavish_graves(const TSP& tsp);
    std::unique_ptr<TSPSolver> init_nearest_neighbour(const TSP& tsp);
}

#endif
