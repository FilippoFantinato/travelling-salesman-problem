#ifndef TSPSOLVER_H
#define TSPSOLVER_H

#include "../tsp/tsp.h"
#include "../path/path.h"

class TSPSolver
{
protected:
    const TSP& tsp;
    const std::string& name;

public:
    TSPSolver(const TSP& tsp, const std::string& name);
    virtual ~TSPSolver() = default;

    virtual double solve() = 0;
    virtual std::shared_ptr<Path> get_best_cycle() const = 0;
    virtual double get_solution_cost() const = 0;
};

#endif
