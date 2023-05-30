#ifndef TOUR_H
#define TOUR_H

#include <vector>
#include <algorithm>

#include "VertexPair.h"
#include "../tsp/tsp.h"

class Tour : public std::vector<VertexPair>
{
private:
    const std::vector<Vertex>& tour;
    double cost;
    double gain;

public:
    explicit Tour(const std::vector<Vertex>&);

    int index(const Vertex& v) const;
    int index(const VertexPair& u_v) const;

    std::vector<Vertex> around(const Vertex& v) const;
    std::vector<VertexPair> around(const VertexPair& u_v) const;

    std::vector<Vertex>* generate(const std::vector<VertexPair>&, const std::vector<VertexPair>&) const;
};

#endif
