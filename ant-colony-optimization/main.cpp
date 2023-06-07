#include <iostream>
#include <vector>
#include <memory>

#include "../libraries/tsp-file/tsp-file.h"
#include "../libraries/utils/measure-time.h"
#include "ACO.h"

#include "../nearest-neighbour/NearestNeighbour.h"

double mean_tsp_distance(const TSP& tsp)
{
    const auto& vertices = tsp.get_vertices();
    auto N = tsp.get_n();

    double sum = 0;
    double n_elements = (N*(N-1)) / 2;
    for(auto i = vertices.cbegin(); i != vertices.end(); ++i)
    {
        Vertex v = *i;
        ++i;
        for(auto j = i; j != vertices.end(); ++j)
        {
            Vertex u = *j;
            sum += tsp.get_weight(v, u);
        }
    }
    return sum / n_elements;
}

int main(int argc, char const *argv[])
{
    const std::string file = argv[1];
    std::ifstream ifd(file);

    if(!ifd.is_open())
    {
        std::cerr << "File " << file << " doesn't exist" << std::endl;
        return 1;
    }

    auto information_tsp = TSPFile::init_tsp_from_file(ifd);

    std::shared_ptr<const TSPFile::TSPInformation> info = information_tsp.first;
    std::shared_ptr<const TSP> tsp = information_tsp.second;

//        auto pheromone = mean_tsp_distance(*tsp);
    auto pheromone_level = NearestNeighbour(*tsp, *tsp->get_vertices().begin()).solve();
    auto iterations = 100;
    auto n_ants = 300;
    double alpha  = 0.9;
    double beta   = 1.5;
    double q      = 10;
    double evaporation_factor = 0.9;
    ACO solver(
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
    std::cout << "Object function value: " << obj_value << std::endl;

    std::shared_ptr<Path> path = solver.get_best_cycle();
    std::cout << "Best cycle: " << *path << std::endl;
    std::cout << "Size of cycle: " << std::set<Vertex>(path->begin(), path->end()).size() << std::endl;

    return 0;
}
