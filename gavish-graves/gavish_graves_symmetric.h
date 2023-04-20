#ifndef GAVISH_GRAVES_SYMMETRIC_H
#define GAVISH_GRAVES_SYMMETRIC_H

#include <vector>

#include "../libraries/tsp/solvers/TSPCPXSolver.h"

class GavishGravesSymmetric : public TSPCPXSolver
{
public:
    GavishGravesSymmetric(const TSP& tsp, const std::string& name = "");

    void build() override;
};

#endif
