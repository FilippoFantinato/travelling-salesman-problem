#ifndef TSP_CLI_H
#define TSP_CLI_H

#include <vector>
#include <unordered_set>

#include "../libraries/tsp-file/tsp-file.h"
#include "../libraries/utils/utils.h"
#include "../libraries/utils/math.h"

#include "./initializers.h"

using TSPFile::TSPInformation;

namespace CLI
{
    typedef struct {
        std::shared_ptr<const Path> path; 
        double cost; 
        double running_time;
    } Solution;
    typedef std::vector<Solution> Solutions;
    typedef std::pair<std::shared_ptr<const TSPInformation>, std::shared_ptr<const Solutions>> InfoSolutions;

    typedef struct {
        double best_error; 
        double worst_error; 
        double avg_error; 
        double err_std_dev; 
        double avg_running_time;
    } SingleStatistic;
    typedef std::pair<std::shared_ptr<const TSPInformation>, SingleStatistic> InfoStatistic;
    typedef std::vector<InfoStatistic> InfoStatistics;

    typedef struct {
        double avg_error;
        double avg_running_time;
    } AllStatistic;

    /*!
        \brief run a chosen algorithm on a file t times

        @param algorithm: chosen algorithm 
        @param f: file on which run the algorithm  
        @param times: how many times tun the algorithm on the file
        @return a pair made up by information about the tsp instance, e.g. name, dimension, type, etc.,
                and a vector of solutions
    */
    InfoSolutions run_file(const std::string& algorithm, const std::string& f, long times);

    /*!
        \brief get the already initialized TSPSolver to solve the given tsp according to the algorithm

        @param algorithm: chosen algorithm 
        @param tsp: tsp to solve
        @return the already initialized TSPSolver to solve the given tsp according to the algorithm
    */
    std::unique_ptr<TSPSolver> get_solver(const std::string& algorithm, const TSP& tsp);

    /*!
        \brief compute the statistics of a single instance
        
        @param solutions: the solutions get by an execution of run_file
        @param optimal_solution: the optimal solution value of the solved tsp 
        @return a struct made up by: 
                - best solution among all the solutions;
                - worse solution among all the solutions;
                - standard deviation of the cost;
                - relative error of the best solution w.r.t. the optimal one;
                - relative error of the worse solution w.r.t. the optimal one;
                - the average error of all relative errors w.r.t. the optimal one;
                - the average execution time of the t executions.
    */
    SingleStatistic compute_single_statistic(const Solutions &solutions, double optimal_solution);

    /*!
        \brief compute the statistic of the single statistic

        @param info_statistics: a pair made up by information and statistics about the tsp just solved
        @return a struct made up by the average error of the average errors 
                and the average execution time of the execution times
    */
    AllStatistic compute_all_statistic(const InfoStatistics& info_statistics);

    /*!
        \brief check whether a solver for an algorithm exists
    */
    bool available_algorithm(const std::string& alg);
}

#endif
