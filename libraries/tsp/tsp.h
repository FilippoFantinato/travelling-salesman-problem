#ifndef TSP_H
#define TSP_H

#include <memory>

#include "../graph/Graph.h"
#include "../tspfile/TSPInformation.h"

typedef int Vertex;
typedef double Weight;
typedef std::tuple<Vertex, Vertex, Weight> Edge;
typedef Graph<Vertex, Weight> TSP;

#endif
