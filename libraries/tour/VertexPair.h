#ifndef VERTEX_PAIR_H
#define VERTEX_PAIR_H

#include <utility>

#include "../tsp/tsp.h"

class VertexPair : public std::pair<Vertex, Vertex>
{
public:
    VertexPair(Vertex a, Vertex b);
};

#endif
