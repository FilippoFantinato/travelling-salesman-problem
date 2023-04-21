#ifndef TSPFILE_ATT_H
#define TSPFILE_ATT_H

#include <memory>
#include <vector>
#include <fstream>
#include <sstream>

#include "../types.h"
#include "../../coordinate/ATTPoint.h"
#include "../../utils/tsp.h"

namespace TSPFile::ATT
{
    std::shared_ptr<const TSP> init_tsp(std::ifstream& ifd, int dimension);
    std::shared_ptr<const VertexCoordinates> read_coordinates(std::ifstream& ifd, int dimension);
};

#endif
