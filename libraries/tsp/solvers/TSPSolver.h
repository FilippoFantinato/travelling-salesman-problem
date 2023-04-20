#ifndef TSPSOLVER_H
#define TSPSOLVER_H

#include "../tsp.h"

class TSPSolver
{
protected:
    const TSP& tsp;

public:
    TSPSolver(const TSP& tsp);
    virtual ~TSPSolver() = default;

    virtual double solve() = 0;
};

#endif
