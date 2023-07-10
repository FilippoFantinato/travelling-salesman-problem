#include "CLI.h"

namespace CLI
{
    // Mapping each algorithm to the corresponding solver initalizer
    std::map<std::string, Init::InitSolver> algorithms = {
            {"ant-system", Init::init_ant_system},
            {"ant-colony-system", Init::init_ant_colony_system},
            {"gavish-graves", Init::init_gavish_graves},
            {"nearest-neighbour", Init::init_nearest_neighbour}
    };

    // Set of available algorithms
    std::unordered_set<std::string> available_algorithms = {
            "ant-system",
            "ant-colony-system",
            "gavish-graves",
            "nearest-neighbour"
    };

    InfoSolutions run_file(const std::string& algorithm, const std::string& f, long times)
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
            double cost_solution = solver->get_solution_cost();

            solutions.push_back({solver->get_best_cycle(), cost_solution, time});
        }

        return {info, std::make_shared<const Solutions>(solutions)};
    }

    std::unique_ptr<TSPSolver> get_solver(const std::string& algorithm, const TSP& tsp)
    {
        return algorithms.at(algorithm)(tsp);
    }

    SingleStatistic compute_single_statistic(const CLI::Solutions &solutions, double optimal_solution)
    {
        double cost = solutions[0].cost;
        double time = solutions[0].running_time;

        double error = Math::relative_error(cost, optimal_solution);

        double best_cost = cost;
        double worst_cost = cost;
        double avg_error = error;
        double avg_running_time = time;

        std::vector<double> errors {error};

        int n = solutions.size();

        for(int i = 1; i < n; ++i)
        {
            const auto& s = solutions.at(i);

            cost = s.cost;
            time = s.running_time;

            if(cost < best_cost)
                best_cost = cost;
            else if(cost > worst_cost)
                worst_cost = cost;

            error = Math::relative_error(cost, optimal_solution);

            avg_error += error;
            avg_running_time += time;

            errors.push_back(error);
        }

        avg_error /= n;
        avg_running_time /= n;

        double err_std_dev = Math::std_dev(errors, avg_error);
        double best_error = Math::relative_error(best_cost, optimal_solution);
        double worst_error = Math::relative_error(worst_cost, optimal_solution);

        return {best_error, worst_error, avg_error, err_std_dev, avg_running_time};
    }

    AllStatistic compute_all_statistic(const InfoStatistics& info_statistics)
    {
        double avg_error = 0;
        double avg_running_time = 0;
        int n = info_statistics.size();

        for(const auto& info_statistic : info_statistics)
        {
            const auto& statistic = info_statistic.second;

            avg_error += statistic.avg_error;
            avg_running_time += statistic.avg_running_time;
        }

        avg_error /= n;
        avg_running_time /= n;

        return {avg_error, avg_running_time};
    }

    bool available_algorithm(const std::string& alg)
    {
        return available_algorithms.count(alg) != 0;
    }
}
