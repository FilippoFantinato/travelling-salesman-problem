#include "initializers.h"

namespace Init
{
    std::unique_ptr<TSPSolver> init_ant_system(const TSP& tsp)
    {
        double w_avg = 0;
        for(const auto& e: tsp.get_edges())
        {
            double w = std::get<2>(e);
            w_avg += w;
        }
        w_avg /= tsp.get_m();

        double pheromone_level = w_avg;
        auto iterations = 50;
        auto n_ants     = tsp.get_n();
        double alpha    = 0.9;
        double beta     = 1.5;
        double q        = 10;
        double rho      = 0.9;
        std::unique_ptr<AntSystem> solver = std::make_unique<AntSystem>(
                tsp,
                pheromone_level,
                iterations,
                n_ants,
                alpha,
                beta,
                q,
                rho);

        return solver;
    }

    std::unique_ptr<TSPSolver> init_ant_colony_system(const TSP& tsp)
    {
        double pheromone_level = 1/(tsp.get_n() * NearestNeighbour(tsp, *tsp.get_vertices().begin()).solve());
        int iterations = 50;
        int n_ants = tsp.get_n();
        double alpha = 0.1;
        double beta  = 2;
        double q0    = 0.9;
        double rho   = 0.1;

        std::unique_ptr<AntColonySystem> solver = std::make_unique<AntColonySystem>(
                tsp,
                pheromone_level,
                iterations,
                n_ants,
                alpha,
                beta,
                q0,
                rho);

        return solver;
    }

    std::unique_ptr<TSPSolver> init_gavish_graves(const TSP& tsp)
    {
        std::unique_ptr<GavishGraves> solver = std::make_unique<GavishGraves>(
                tsp,
                *tsp.get_vertices().begin());

        solver->build();

        return solver;
    }

    std::unique_ptr<TSPSolver> init_nearest_neighbour(const TSP& tsp)
    {
        return std::make_unique<NearestNeighbour>(tsp, *tsp.get_vertices().begin());
    }
}
