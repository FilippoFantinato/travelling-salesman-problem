#ifndef TSPFILE_UPPER_ROW_H
#define TSPFILE_UPPER_ROW_H

#include <memory>
#include <string>
#include <fstream>
#include <sstream>

#include "../types.h"

namespace TSPFile::UPPER_ROW
{
    std::shared_ptr<const TSP> init_tsp(std::ifstream& ifd, int dimension);
};

#endif
