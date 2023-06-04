#ifndef TSP_H
#define TSP_H

#include "../graph/SparseGraph.h"
#include "../graph/DenseGraph.h"
#include "../tsp-file/TSPInformation.h"

typedef int Vertex;
typedef double Weight;
typedef std::tuple<Vertex, Vertex, Weight> Edge;
typedef DenseGraph<Vertex, Weight> TSP;

#endif
