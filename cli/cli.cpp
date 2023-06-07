#include "cli.h"

namespace CLI
{
    std::map<std::string, Init::InitSolver> algorithms = {
            {"ant-colony-optimization", Init::init_ant_colony_optimization},
            {"ant-colony-system", Init::init_ant_colony_system},
            {"gavish-graves", Init::init_gavish_graves},
            {"nearest-neighbour", Init::init_nearest_neighbour}
    };

    int run_file(const char *algorithm, const char *f, long times)
    {
        std::ifstream ifd(f);

        if(!ifd.is_open())
        {
            std::cerr << "File " << f << " doesn't exist" << std::endl;
            return 1;
        }

        auto information_tsp = TSPFile::init_tsp_from_file(ifd);

        std::shared_ptr<const TSPFile::TSPInformation> info = information_tsp.first;
        std::shared_ptr<const TSP> tsp = information_tsp.second;

        std::unique_ptr<TSPSolver> solver = get_solver(algorithm, *tsp);

        double time = Utils::measure_time([&solver](){
            solver->solve();
        });
        double obj_value = solver->get_solution_cost();

        std::cout << *info << std::endl << std::endl;
        std::cout << "Execution time: " << time << "s" << std::endl;
        std::cout << "Object function value: " << obj_value << std::endl;

        std::shared_ptr<Path> path = solver->get_best_cycle();
        std::cout << "Best cycle: " << *path << std::endl;
        std::cout << "Size of cycle: " << std::set<Vertex>(path->begin(), path->end()).size() << std::endl;

        return 0;
    }

    std::unique_ptr<TSPSolver> get_solver(const char *algorithm, const TSP& tsp)
    {
        return algorithms.at(algorithm)(tsp);
    }
}