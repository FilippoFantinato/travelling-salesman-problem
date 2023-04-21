#ifndef UTILS_TSP_H
#define UTILS_TSP_H

#include <memory>
#include <fstream>

#include "../coordinate/Coordinate.h"
#include "../tspfile/types.h"

namespace Utils
{
    std::shared_ptr<const TSP> tsp_from_coordinates(std::shared_ptr<const TSPFile::VertexCoordinates> coordinates);
};

#endif
