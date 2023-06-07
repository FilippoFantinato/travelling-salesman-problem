#ifndef TSPFILE_TYPES_H
#define TSPFILE_TYPES_H

#include <memory>
#include <fstream>

#include "../coordinate/Coordinate.h"
#include "../tsp/tsp.h"

namespace TSPFile
{
    typedef std::pair<Vertex, std::shared_ptr<Coordinate>> VertexCoordinate;
    typedef std::set<VertexCoordinate> VertexCoordinates;
}

#endif
