#ifndef TSP_FILE_H
#define TSP_FILE_H

#include <iostream>
#include <set>
#include <memory>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>

#include "../exceptions/EdgeWeightNotHandled.h"

#include "types.h"
#include "TSPSection.h"
#include "TSPInformation.h"
#include "../tsp-readers/euc2d.h"
#include "../tsp-readers/att.h"
#include "../tsp-readers/geo.h"
#include "../tsp-readers/full_matrix.h"
#include "../tsp-readers/upper_row.h"

namespace TSPFile
{
    typedef std::shared_ptr<const TSP> (*TSPHandler)(std::ifstream &ifd, int dimension);
    typedef std::pair<std::shared_ptr<const TSPInformation>, std::shared_ptr<const TSP>> PairInformationTSP;

    PairInformationTSP init_tsp_from_file(std::ifstream &ifd);
    TSPHandler choose_tsp_handler(const TSPInformation& info);
}

#endif
