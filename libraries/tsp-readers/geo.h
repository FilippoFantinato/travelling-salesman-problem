#ifndef TSPFILE_GEO_H
#define TSPFILE_GEO_H

#include <memory>
#include <sstream>

#include "../tsp-file/TSPSection.h"
#include "../tsp-file/types.h"
#include "../tsp/tsp.h"
#include "../coordinate/GeoLocation.h"
#include "../utils/trim.h"
#include "../utils/tsp.h"

namespace TSPFile::GEO
{
    std::shared_ptr<const TSP> init_tsp(std::ifstream& ifd, int dimension);
    std::shared_ptr<const VertexCoordinates> read_coordinates(std::ifstream& ifd, int dimension);
};

#endif
