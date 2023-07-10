#include <iostream>
#include <vector>
#include <memory>

#include "../libraries/tsp-file/tsp-file.h"
#include "../libraries/utils/utils.h"
#include "AntSystem.h"

double average_distance(const TSP& tsp)
{
    double avg = 0;
    for(const auto& e: tsp.get_edges())
    {
        double w = std::get<2>(e);
        avg += w;
    }
    return avg / tsp.get_m();
}

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

    auto pheromone_level = average_distance(*tsp);
    auto iterations = 50;
    auto n_ants = tsp->get_n();
    double alpha  = 0.9;
    double beta   = 1.5;
    double q      = 10;
    double evaporation_factor = 0.9;
    AntSystem solver(
            *tsp,
            pheromone_level,
            iterations,
            n_ants,
            alpha,
            beta,
            q,
            evaporation_factor);

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
