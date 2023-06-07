#include "initializers.h"

namespace Init
{
    std::unique_ptr<TSPSolver> init_ant_colony_optimization(const TSP& tsp)
    {
        auto pheromone_level = NearestNeighbour(tsp, *tsp.get_vertices().begin()).solve();
        auto iterations = 100;
        auto n_ants = 300;
        double alpha  = 0.9;
        double beta   = 1.5;
        double q      = 10;
        double evaporation_factor = 0.9;
        std::unique_ptr<ACO> solver = std::make_unique<ACO>(
                tsp,
                pheromone_level,
                iterations,
                n_ants,
                alpha,
                beta,
                q,
                evaporation_factor);

        return solver;
    }

    std::unique_ptr<TSPSolver> init_ant_colony_system(const TSP& tsp)
    {
        double pheromone_level = NearestNeighbour(tsp, *tsp.get_vertices().begin()).solve();
        int iterations = 100;
        int n_ants = 100;
        double beta = 2;
        double q0   = 0.9;
        double rho  = 0.1;
        double evaporation_factor = 0.1;

        std::unique_ptr<ACS> solver = std::make_unique<ACS>(
                tsp,
                pheromone_level,
                iterations,
                n_ants,
                beta,
                q0,
                rho,
                evaporation_factor);

        return solver;
    }

    std::unique_ptr<TSPSolver> init_gavish_graves(const TSP& tsp)
    {
        return std::make_unique<GavishGraves>(tsp, *tsp.get_vertices().begin());
    }

    std::unique_ptr<TSPSolver> init_nearest_neighbour(const TSP& tsp)
    {
        return std::make_unique<NearestNeighbour>(tsp, *tsp.get_vertices().begin());
    }
}
