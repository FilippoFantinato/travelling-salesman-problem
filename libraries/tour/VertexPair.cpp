#include "VertexPair.h"


VertexPair::VertexPair(Vertex a, Vertex b) :
    std::pair<Vertex, Vertex>(a <= b ? std::make_pair(a, b) : std::make_pair(b, a))
{ }
