#include <iostream>
#include <vector>
#include <memory>

#include "../libraries/tsp-file/tsp-file.h"
#include "../libraries/utils/measure-time.h"
#include "NearestNeighbour.h"

int main(int argc, char const *argv[])
{
    const std::string file = argv[1];
    std::ifstream ifd(file);

    if(ifd.is_open())
    {
        std::shared_ptr<const TSPFile::PairInformationTSP> information_tsp = TSPFile::init_tsp_from_file(ifd);

        auto info = information_tsp->first;
        auto tsp = information_tsp->second;

        auto solver(new NearestNeighbour(*tsp, *tsp->get_vertices().begin()));

        double time = Utils::measure_time([&solver](){
            solver->solve();
        });
        double obj_value = solver->get_solution_cost();

        std::cout << *info << std::endl << std::endl;
        std::cout << "Execution time: " << time << "s" << std::endl;
        std::cout << "Object function value: " << obj_value << std::endl;

        auto path = solver->get_best_cycle();

        std::cout << "Best cycle: ";
        for(const auto& el : *path)
        {
            std::cout << el << " ";
        }
        std::cout << std::endl;

//        std::cout << "Size of cycle: " << std::set(path->begin(), path->end()).size() << std::endl;
    }
    else
    {
        std::cerr << "File " << file << " doesn't exist" << std::endl;
    }

    return 0;
}
