#ifndef ANTCOLONY_H
#define ANTCOLONY_H

#include <cmath>
#include <iterator>
#include <future>
#include <thread>

#include "../libraries/path/path.h"
#include "../libraries/tsp-solvers/TSPSolver.h"
#include "../libraries/utils/random.h"


class AntColony : public TSPSolver
{
private:
    const double iteration;
    const double n_ants;
    const double alpha;
    const double beta;
    const double q;
    const double evaporation_factor;

    std::unique_ptr<std::unique_ptr<double[]>[]> intensity;

    std::shared_ptr<Path> best_cycle;
    double best_cost = std::numeric_limits<double>::infinity();

    std::shared_ptr<Path> ant(Vertex source_node) const;

    void update_intensity(const std::vector<std::shared_ptr<Path>> &cycles);

public:
    AntColony(const TSP& tsp,
              double pheromone_level,
              double iteration,
              double n_ants,
              double alpha  = 0.9,
              double beta   = 1.5,
              double q      = 10,
              double evaporation_factor = 0.9,
              const std::string& name = "");

    double solve() override;
    double get_solution_cost() const override;
    std::shared_ptr<Path> get_best_cycle() const;
    void write_file(const std::string &directory) override {}
};

#endif