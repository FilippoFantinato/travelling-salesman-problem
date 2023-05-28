#include "VertexPair.h"


VertexPair::VertexPair(const Vertex& u, const Vertex& v) :
    std::pair<Vertex, Vertex>(u < v ? std::make_pair(u, v) : std::make_pair(v, u)) 
{ }
