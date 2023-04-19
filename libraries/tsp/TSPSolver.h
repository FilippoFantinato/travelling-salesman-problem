#ifndef TSPSOLVER_H
#define TSPSOLVER_H

#include "tsp.h"
#include "../cpxmacro.h"

class TSPSolver
{
protected:
    const TSP& tsp;

public:
    TSPSolver(const TSP& tsp) : tsp(tsp) { }

    virtual double solve() = 0;
};

#endif
