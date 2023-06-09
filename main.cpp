#include <iostream>
#include <functional>
#include <getopt.h>
#include <iomanip>
#include <filesystem>
#include <cmath>

#include "./libraries/utils/math.h"
#include "./cli/cli.h"

namespace fs = std::filesystem;
using TSPInformation = TSPFile::TSPInformation;

void print_usage()
{
    std::cerr << "usage: tsp --algorithm a [--file f] [--times t]" << std::endl;
    std::cerr << "\t--algorithm a \t: ..." << std::endl;
    std::cerr << "\t--file f \t: ..." << std::endl;
    std::cerr << "\t--times t \t: ..." << std::endl;
}

typedef std::tuple<double, double, double, double, double> Statistic;
typedef std::vector<Statistic> Statistics;
typedef std::pair<std::shared_ptr<const TSPInformation>, Statistic> InfoStatistic;
typedef std::vector<InfoStatistic> InfoStatistics;

Statistic compute_statistics(const CLI::Solutions &solutions, double optimal_solution)
{
    double best_cost = solutions[0].cost;
    double worst_cost = solutions[0].cost;
    double average_cost = solutions[0].cost;
    double average_running_time = solutions[0].time;

    int n = solutions.size();

    std::vector<double> costs {solutions[0].cost};

    for(int i = 1; i < n; ++i)
    {
        const Solution& s = solutions.at(i);
        if(s.cost < best_cost)
        {
            best_cost = s.cost;
        } else if(s.cost > worst_cost)
        {
            worst_cost = s.cost;
        }

        average_cost += s.cost;
        average_running_time += s.time;
        costs.push_back(s.cost);
    }

    average_running_time /= n;
    average_cost /= n;

    double cost_std_dev = Math::std_dev(costs, average_cost);
    double error = Math::round((best_cost - optimal_solution) / optimal_solution, 4);

    return {best_cost, worst_cost, cost_std_dev, error, average_running_time};
}

void print_measurement_data(const InfoStatistics& info_statistics)
{
    int padding = 15;
    std::vector<std::string> headers =
            {"Name", "Opt. Solution", "Best solution", "Worst solution", "Cost Std. dev.", "Error", "Avg. Time (s)"};

    for(const auto& header: headers)
    {
        std::cout << std::setw(padding) << header << " | ";
    }
    std::cout << std::endl;

    std::cout << std::string(padding*(headers.size() + 2), '-') << std::endl;

    for(const auto& info_statistic: info_statistics)
    {
        const auto& info = *info_statistic.first;
        const auto& s = info_statistic.second;

        double best = std::get<0>(s);
        double worst = std::get<1>(s);
        double cost_std_dev = std::get<2>(s);
        double error = std::get<3>(s);
        double avg_time = std::get<4>(s);

        std::cout << std::setw(padding) << info.name << " | ";
        std::cout << std::setw(padding) << info.optimal_solution << " | ";
        std::cout << std::setw(padding) << best << " | ";
        std::cout << std::setw(padding) << worst << " | ";
        std::cout << std::setw(padding) << cost_std_dev << " | ";
        std::cout << std::setw(padding) << error << " | ";
        std::cout << std::setw(padding) << avg_time << " | ";
        std::cout << std::endl;
    }
}

int main(int argc, char *argv[])
{
    option longopts[] = {
            {"file", required_argument, nullptr, 'f'},
            {"algorithm", required_argument, nullptr, 'a'},
            {"times", optional_argument, nullptr, 't'}
    };

    char *algorithm = nullptr;
    char *file = nullptr;
    char *directory = nullptr;
    long times = 1;

    int opt;
    while((opt = getopt_long(argc, argv, "a:d:f:t:", longopts, nullptr)) != EOF)
    {
        switch (opt) {
            case 'a':
                algorithm = optarg;
                break;
            case 'f':
                file = optarg;
                break;
            case 'd':
                directory = optarg;
                break;
            case 't':
                times = strtol(optarg, nullptr, 10);
                break;
            default:
                print_usage();
        }
    }

    if(!algorithm || (!file && !directory))
    {
        print_usage();
        return 1;
    }

    InfoStatistics info_statistics;

    if(file)
    {
        CLI::InfoSolutions info_solutions= CLI::run_file(algorithm, file, times);

        auto info = info_solutions.first;
        auto solutions = info_solutions.second;
        auto statistic = compute_statistics(*solutions, info->optimal_solution);

        info_statistics.emplace_back(info, statistic);
    } else {
        for (const auto& entry : fs::directory_iterator(directory))
        {
            const char *file_path = entry.path().c_str();

            std::cout << "Running " << file_path << "..." << std::endl;

            CLI::InfoSolutions info_solutions= CLI::run_file(algorithm, file_path, times);
            auto info = info_solutions.first;
            auto solutions = info_solutions.second;
            auto statistic = compute_statistics(*solutions, info->optimal_solution);

            info_statistics.emplace_back(info, statistic);
        }
    }

    print_measurement_data(info_statistics);
}
