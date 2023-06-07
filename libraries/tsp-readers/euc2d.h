#ifndef TSPFILE_EUC2D_H
#define TSPFILE_EUC2D_H

#include <memory>
#include <sstream>
#include <cmath>

#include "../tsp-file/types.h"
#include "../tsp/tsp.h"
#include "../coordinate/Point.h"
#include "../utils/tsp.h"

namespace TSPFile::EUC2D
{
    std::shared_ptr<const TSP> init_tsp(std::ifstream& ifd, int dimension);
    std::shared_ptr<const VertexCoordinates> read_coordinates(std::ifstream& ifd, int dimension);
}

#endif
