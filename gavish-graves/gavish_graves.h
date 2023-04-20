#ifndef GAVISHGRAVES_H
#define GAVISHGRAVES_H

#include <vector>
#include "../libraries/tsp/TSPCPXSolver.h"

class GavishGraves : public TSPCPXSolver
{
public:
    GavishGraves(
        const TSP& tsp,
        bool debug = false,
        const std::string& name = ""
    ) : TSPCPXSolver(tsp, debug, name) { }

    void build() override;
};

#endif
