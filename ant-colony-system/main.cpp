#include <iostream>
#include <memory>

#include "../libraries/tsp-file/tsp-file.h"
#include "../libraries/utils/utils.h"
#include "AntColonySystem.h"

#include "../nearest-neighbour/NearestNeighbour.h"

int main(int argc, char const *argv[])
{
    const std::string file = argv[1];
    std::ifstream ifd(file);

    if(!ifd.is_open())
    {
        throw std::runtime_error((std::string("Cannot find file ") + std::string(file)).c_str());
    }

    auto information_tsp = TSPFile::init_tsp_from_file(ifd);

    std::shared_ptr<const TSPFile::TSPInformation> info = information_tsp.first;
    std::shared_ptr<const TSP> tsp = information_tsp.second;

    double pheromone_intensity = 1/(tsp->get_n() * NearestNeighbour(*tsp, *tsp->get_vertices().begin()).solve());
    int iterations = 50;
    int n_ants = tsp->get_n();
    double alpha = 0.1;
    double beta  = 2;
    double q0    = 0.9;
    double rho   = 0.1;

    AntColonySystem solver(
            *tsp,
            pheromone_intensity,
            iterations,
            n_ants,
            alpha,
            beta,
            q0,
            rho);

    double time = Utils::measure_time([&solver](){
        solver.solve();
    });
    double obj_value = solver.get_solution_cost();

    std::cout << *info << std::endl << std::endl;
    std::cout << "Execution time: " << time << "s" << std::endl;
    std::cout << "Best cycle cost: " << obj_value << std::endl;

    std::shared_ptr<Path> path = solver.get_best_cycle();
    std::cout << "Best cycle: " << *path << std::endl;

    return 0;
}
