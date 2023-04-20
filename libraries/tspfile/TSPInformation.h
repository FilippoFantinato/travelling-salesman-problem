#ifndef TSPINFORMATION_H
#define TSPINFORMATION_H

#include <iostream>
#include <string>
#include <map>
#include <exception>
#include <memory>
#include <fstream>

#include "TSPSection.h"
#include "../tsp/exceptions.h"
#include "../utils/trim.h"

namespace TSPFile
{
    struct TSPInformation
    {
        std::string name;
        std::string comment;
        std::string type;
        std::string edge_weight_type;
        int dimension;
        int optimal_solution = -1;
    };

    std::shared_ptr<const TSPInformation> read_information(std::ifstream &ifd);
};

#endif
