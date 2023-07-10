#ifndef TSP_INITIALIZERS_H
#define TSP_INITIALIZERS_H

#include <memory>

#include "../libraries/tsp/tsp.h"

#include "../libraries/tsp-solvers/TSPSolver.h"
#include "../ant-system/AntSystem.h"
#include "../ant-colony-system/AntColonySystem.h"
#include "../gavish-graves/GavishGraves.h"
#include "../nearest-neighbour/NearestNeighbour.h"

namespace Init
{
    typedef std::function<std::unique_ptr<TSPSolver>(const TSP&)> InitSolver;

    /*! \brief inializer for Ant System metaheuristic */
    std::unique_ptr<TSPSolver> init_ant_system(const TSP& tsp);

    /*! \brief inializer for Ant Colony System metaheuristic */
    std::unique_ptr<TSPSolver> init_ant_colony_system(const TSP& tsp);
    
    /*! \brief inializer for Gavish graves exact method MILP */
    std::unique_ptr<TSPSolver> init_gavish_graves(const TSP& tsp);
    
    /*! \brief inializer for Nearest Neighbour heuristic */
    std::unique_ptr<TSPSolver> init_nearest_neighbour(const TSP& tsp);
}

#endif
