#ifndef GAVISHGRAVES_H
#define GAVISHGRAVES_H

#include "Graph.h"
#include "../libraries/cpxmacro.h"

typedef int Vertex;
typedef double Weight;
typedef std::tuple<Vertex, Vertex, Weight> Edge;
typedef Graph<Vertex, Weight> TSP;

namespace GavishGraves
{
    void solve_tsp(CEnv env, Prob lp, const std::unique_ptr<TSP>& tsp)
};

#endif GAVISHGRAVES_H

