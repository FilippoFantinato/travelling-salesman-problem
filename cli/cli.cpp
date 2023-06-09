#include "cli.h"

namespace CLI
{
    std::map<std::string, Init::InitSolver> algorithms = {
            {"ant-colony-optimization", Init::init_ant_colony_optimization},
            {"ant-colony-system", Init::init_ant_colony_system},
            {"gavish-graves", Init::init_gavish_graves},
            {"nearest-neighbour", Init::init_nearest_neighbour}
    };

    InfoSolutions run_file(const char *algorithm, const char *f, long times)
    {
        std::ifstream ifd(f);

        if(!ifd.is_open())
        {
            throw std::runtime_error((std::string("Cannot find file ") + std::string(f)).c_str());
        }

        auto information_tsp = TSPFile::init_tsp_from_file(ifd);

        std::shared_ptr<const TSPFile::TSPInformation> info = information_tsp.first;
        std::shared_ptr<const TSP> tsp = information_tsp.second;

        Solutions solutions;
        for(int i = 0; i < times; ++i)
        {
            std::unique_ptr<TSPSolver> solver = get_solver(algorithm, *tsp);
            double time = Utils::measure_time([&solver](){
                solver->solve();
            });
            double obj_value = solver->get_solution_cost();

            solutions.emplace_back(solver->get_best_cycle(), obj_value, time);
        }


//        std::cout << *info << std::endl << std::endl;
//        std::cout << "Execution time: " << time << "s" << std::endl;
//        std::cout << "Object function value: " << obj_value << std::endl;
//
//        std::shared_ptr<Path> path = solver->get_best_cycle();
//        std::cout << "Best cycle: " << *path << std::endl;
//        std::cout << "Size of cycle: " << std::set<Vertex>(path->begin(), path->end()).size() << std::endl;

        return {info, std::make_shared<const Solutions>(solutions)};
    }

    std::unique_ptr<TSPSolver> get_solver(const char *algorithm, const TSP& tsp)
    {
        return algorithms.at(algorithm)(tsp);
    }
}