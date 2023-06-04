#ifndef ANTCOLONY_H
#define ANTCOLONY_H

#include <cmath>
#include <iterator>
#include <future>
#include <thread>

#include "../libraries/tour/Tour.h"
#include "../libraries/tsp-solvers/TSPSolver.h"
#include "../libraries/utils/random.h"

typedef std::shared_ptr<std::vector<Vertex>> VertexVector_ptr;

class AntColony : public TSPSolver
{
private:
    const double iteration;
    const double n_ants;
    const double q;
    const double degradation_factor;

    std::unique_ptr<std::unique_ptr<double[]>[]> intensity;

    VertexVector_ptr best_cycle;
    double best_cost = std::numeric_limits<double>::infinity();

    std::shared_ptr<std::vector<Vertex>> traverse_graph(Vertex source_node) const;

public:
    AntColony(
            const TSP& tsp,
            double pheromone_level,
            double iteration,
            double n_ants,
            const std::string& name = "",
            double q = 10,
            double degradation_factor = 0.9);

    double solve() override;
    double get_solution_cost() const override;
    void write_file(const std::string &directory) override {}
};

#endif