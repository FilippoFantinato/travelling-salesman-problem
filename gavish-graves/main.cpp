#include <iostream>
#include <vector>
#include <memory>

#include "../libraries/tsp-file/tsp-file.h"
#include "../libraries/utils/measure-time.h"
#include "GavishGraves.h"

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

    try
    {
        GavishGraves solver(*tsp, *tsp->get_vertices().begin());

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
    catch(const std::exception& e)
    {
        std::cerr << ">>>EXCEPTION: " << e.what() << std::endl;
    }

	return 0;
}
