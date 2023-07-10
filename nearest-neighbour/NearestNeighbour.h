#ifndef TSP_NEAREST_NEIGHBOUR_H
#define TSP_NEAREST_NEIGHBOUR_H

#include "../libraries/tsp-solvers/TSPSolver.h"

class NearestNeighbour : public TSPSolver
{
private:
    const Vertex starting_node;

    std::shared_ptr<Path> best_cycle;
    double best_cost = std::numeric_limits<double>::infinity();

public:
    NearestNeighbour(const TSP& tsp,
                     Vertex starting_node,
                     const std::string& name = "");

    double solve() override;
    double get_solution_cost() const override;
    std::shared_ptr<Path> get_best_cycle() const override;
};


#endif