#ifndef TSPFILE_H
#define TSPFILE_H

#include <iostream>
#include <set>
#include <memory>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>

#include "../tsp/exceptions/EdgeWeightNotHandled.h"

#include "types.h"
#include "TSPSection.h"
#include "TSPInformation.h"
#include "readers/euc2d.h"
#include "readers/att.h"
#include "readers/geo.h"
#include "readers/full_matrix.h"
#include "readers/upper_row.h"

namespace TSPFile
{
    typedef std::shared_ptr<const TSP> (*TSPHandler)(std::ifstream &ifd, int dimension);
    typedef std::pair<std::shared_ptr<const TSPInformation>, std::shared_ptr<const TSP>> PairInformationTSP;

    std::shared_ptr<const PairInformationTSP> init_tsp_from_file(std::ifstream &ifd);
    TSPHandler choose_tsp_handler(const TSPInformation& info);
};

#endif
