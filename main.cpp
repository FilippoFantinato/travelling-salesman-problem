#include <iostream>
#include <functional>
#include <getopt.h>
#include <iomanip>
#include <set>
#include <filesystem>
#include <cmath>

#include "./CLI/CLI.h"

namespace fs = std::filesystem;

using namespace CLI;

/*!
    \brief print the usage message
*/
void print_usage()
{
    std::cerr << "usage: tsp [-h] -a algorithm [-f file | -d directory] [-t t=1]" << std::endl;
    std::cerr << "\t-h \t\t: for showing this help message." << std::endl;
    std::cerr << "\t-a algorithm \t: choosing one of the supported algorithms." << std::endl;
    std::cerr << "\t-f file \t: path to the file in tsp format." << std::endl;
    std::cerr << "\t-d directory \t: path to the directory with file in tsp format." << std::endl;
    std::cerr << "\t-t t=1 \t\t: repeat the execution of the algorithm t times. By default is set to 1." << std::endl;
}


/*!
    \brief print all measurement data as a table

    @param info_statistics: a vector containing pairs (info, statistics) for each instance
    @param all_statistic: statistics about info_statistics
*/
void print_measurement_data(
        const InfoStatistics& info_statistics,
        const AllStatistic& all_statistic)
{
    int padding = 20;
    std::vector<std::string> headers =
            {"Name", "Opt. solution", "Best error (%)", "Worst error (%)", 
             "Avg. error (%)", "Err. std. dev. (%)", "Avg. time (s)"};

    for(const auto& header: headers)
    {
        std::cout << std::setw(padding) << header << " |";
    }
    std::cout << std::endl;

    std::cout << std::string(padding*(headers.size()) + 14, '-') << std::endl;

    for(const auto& info_statistic: info_statistics)
    {
        const auto& info = *info_statistic.first;
        const auto& s = info_statistic.second;

        std::cout << std::setw(padding) << info.name << " |";
        std::cout << std::setw(padding) << info.optimal_solution << " |";
        std::cout << std::setw(padding) << Math::round(s.best_error*100, 2) << " |";
        std::cout << std::setw(padding) << Math::round(s.worst_error*100, 2) << " |";
        std::cout << std::setw(padding) << Math::round(s.avg_error*100, 2) << " |";
        std::cout << std::setw(padding) << Math::round(s.err_std_dev*100, 2) << " |";
        std::cout << std::setw(padding) << Math::round(s.avg_running_time, 3) << " |";
        std::cout << std::endl;
    }

    std::cout << "Avg. error (%): "
              << Math::round(all_statistic.avg_error*100, 2) << std::endl;
    std::cout << "Avg. time (s): " 
              << Math::round(all_statistic.avg_running_time, 3) << std::endl;
}

int main(int argc, char *argv[])
{
    // Read the options from CLI
    char *algorithm = nullptr;
    char *input_file = nullptr;
    char *directory = nullptr;
    long times = 1;

    int opt;
    while((opt = getopt(argc, argv, "ha:d:f:t:")) != EOF)
    {
        switch (opt) {
            case 'a':
                algorithm = optarg;
                break;
            case 'f':
                input_file = optarg;
                break;
            case 'd':
                directory = optarg;
                break;
            case 't':
                times = strtol(optarg, nullptr, 10);
                break;

            case 'h':
            default:
                print_usage();
                return 0;
        }
    }

    // Check there is any error and print the usage command if so
    if((!algorithm || !available_algorithm(algorithm)) || (!input_file && !directory))
    {
        print_usage();
        return 1;
    }

    InfoStatistics info_statistics;

    if(input_file)
    {
        InfoSolutions info_solutions= run_file(algorithm, input_file, times);

        auto info = info_solutions.first;
        auto solutions = info_solutions.second;
        auto statistic = compute_single_statistic(*solutions, info->optimal_solution);

        info_statistics.emplace_back(info, statistic);
    } else {
        // Read all the .tsp files in the given directory and sort them
        std::set<std::string> filenames;
        for (const auto& entry : fs::directory_iterator(directory))
        {
            if(fs::path(entry.path()).extension() == ".tsp")
            {
                filenames.insert(entry.path().string());
            }
        }

        // Run the chosen algorithm on each file t times, computing the statistics  
        for(const auto& filename : filenames)
        {
            std::cout << "Running " << filename << "..." << std::endl;

            InfoSolutions info_solutions = run_file(algorithm, filename, times);
            auto info = info_solutions.first;
            auto solutions = info_solutions.second;
            auto statistic = compute_single_statistic(*solutions, info->optimal_solution);

            info_statistics.emplace_back(info, statistic);
        }
    }
    // Compute the statistics of the instance statistics
    auto all_statistic = compute_all_statistic(info_statistics);

    print_measurement_data(info_statistics, all_statistic);
}
