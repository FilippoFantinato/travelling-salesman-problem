#ifndef TSPSOLVER_H
#define TSPSOLVER_H

#include "../tsp/tsp.h"

class TSPSolver
{
protected:
    const TSP& tsp;
    const std::string& name;

public:
    TSPSolver(const TSP& tsp, const std::string& name);
    virtual ~TSPSolver() = default;

    virtual double solve() = 0;
    virtual void write_file(const std::string& directory = "") = 0;
};

#endif
