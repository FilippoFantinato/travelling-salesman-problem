#ifndef GAVISHGRAVES_H
#define GAVISHGRAVES_H

#include <vector>
#include "../libraries/tsp-solvers/TSPCPXSolver.h"

class GavishGraves : public TSPCPXSolver
{
private:
    const Vertex IN;

    int N_Y_VAR;
    int N_X_VAR;

    std::unique_ptr<std::unique_ptr<int[]>[]> map_y;
    std::unique_ptr<std::unique_ptr<int[]>[]> map_x;

public:
    GavishGraves(const TSP& tsp,
                 Vertex IN,
                 const std::string& name = "");

    void build() override;
    std::shared_ptr<Path> get_best_cycle() const override;
};

#endif
