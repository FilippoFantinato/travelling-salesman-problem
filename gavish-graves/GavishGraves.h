#ifndef GAVISHGRAVES_H
#define GAVISHGRAVES_H

#include <vector>
#include "../libraries/tsp-solvers/TSPCPXSolver.h"

class GavishGraves : public TSPCPXSolver
{
private:
    std::map<Vertex, std::map<Vertex, int>> map_x;
    std::map<Vertex, std::map<Vertex, int>> map_y;

public:
    GavishGraves(const TSP& tsp, const std::string& name);

    void build() override;
    std::shared_ptr<Path> get_best_cycle() const override;
};

#endif
