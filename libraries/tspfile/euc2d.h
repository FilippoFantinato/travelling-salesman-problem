#ifndef TSPFILE_EUC2D_H
#define TSPFILE_EUC2D_H

#include <memory>
#include <sstream>
#include <cmath>

#include "TSPSection.h"
#include "types.h"
#include "../tsp/tsp.h"
#include "../coordinate/Point.h"

namespace TSPFile::EUC2D
{
    std::shared_ptr<const TSP> init_tsp(std::ifstream& ifd, int dimension);
    std::shared_ptr<const VertexCoordinates> read_points(std::ifstream& ifd, int dimension);
    std::shared_ptr<const TSP> tsp_from_points(std::shared_ptr<const VertexCoordinates> coordinates);
};

#endif
