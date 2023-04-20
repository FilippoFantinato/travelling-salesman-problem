#ifndef TSPFILE_FULL_MATRIX_H
#define TSPFILE_FULL_MATRIX_H

#include <memory>
#include <string>
#include <fstream>
#include <sstream>

#include "types.h"

namespace TSPFile::FULL_MATRIX
{
    std::shared_ptr<const TSP> init_tsp(std::ifstream& ifd, int dimension);
};

#endif
