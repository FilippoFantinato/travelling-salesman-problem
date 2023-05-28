#ifndef VERTEX_PAIR_H
#define VERTEX_PAIR_H

#include <utility>

#include "../tsp.h"

class VertexPair : public std::pair<Vertex, Vertex>
{
public:
    VertexPair(const Vertex& u, const Vertex& v);
};


#endif
