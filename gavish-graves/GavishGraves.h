#ifndef GAVISHGRAVES_H
#define GAVISHGRAVES_H

#include <vector>
#include "../libraries/tsp-solvers/TSPCPXSolver.h"

class GavishGraves : public TSPCPXSolver
{
public:
    GavishGraves(const TSP& tsp, const std::string& name);

    void build() override;
};

#endif
