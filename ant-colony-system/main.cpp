#include <iostream>
#include <memory>

#include "../libraries/tsp-file/tsp-file.h"
#include "../libraries/utils/measure-time.h"
#include "ACS.h"

#include "../nearest-neighbour/NearestNeighbour.h"

int main(int argc, char const *argv[])
{
    const std::string file = argv[1];
    std::ifstream ifd(file);

    if(ifd.is_open())
    {
        auto information_tsp = TSPFile::init_tsp_from_file(ifd);

        std::shared_ptr<const TSPFile::TSPInformation> info = information_tsp.first;
        std::shared_ptr<const TSP> tsp = information_tsp.second;

        double pheromone_level = NearestNeighbour(*tsp, *tsp->get_vertices().begin()).solve();
        int iterations = 100;
        int n_ants = 100;
        double beta = 2;
        double q0   = 0.9;
        double rho  = 0.1;
        double evaporation_factor = 0.1;

        ACS solver(
                *tsp,
                pheromone_level,
                iterations,
                n_ants,
                beta,
                q0,
                rho,
                evaporation_factor);

        double time = Utils::measure_time([&solver](){
            solver.solve();
        });
        double obj_value = solver.get_solution_cost();

        std::cout << *info << std::endl << std::endl;
        std::cout << "Execution time: " << time << "s" << std::endl;
        std::cout << "Object function value: " << obj_value << std::endl;

        std::shared_ptr<Path> path = solver.get_best_cycle();
        std::cout << "Best cycle: " << *path << std::endl;
        std::cout << "Size of cycle: " << std::set<Vertex>(path->begin(), path->end()).size() << std::endl;
    }
    else
    {
        std::cerr << "File " << file << " doesn't exist" << std::endl;
    }

    return 0;
}
