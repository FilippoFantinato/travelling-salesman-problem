#ifndef TSP_READERS_TYPES_H
#define TSP_READERS_TYPES_H

#include <iostream>
#include <memory>
#include <fstream>
#include <set>
#include <utility>

#include "../tsp/tsp.h"
#include "../coordinate/Coordinate.h"
#include "../tsp-file/TSPInformation.h"

typedef std::pair<Vertex, std::shared_ptr<Coordinate>> VertexCoordinate;
typedef std::set<VertexCoordinate> VertexCoordinates;

#endif
