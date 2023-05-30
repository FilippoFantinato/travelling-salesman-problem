#ifndef TSPINFORMATION_H
#define TSPINFORMATION_H

#include <iostream>
#include <string>
#include <map>
#include <exception>
#include <memory>
#include <fstream>

#include "TSPSection.h"
#include "../exceptions/IncompleteTSPFile.h"
#include "../utils/trim.h"

namespace TSPFile
{
    struct TSPInformation
    {
        std::string name;
        std::string comment;
        std::string type;
        std::string edge_weight_type;
        std::string edge_weight_format;
        int dimension;
        int optimal_solution = -1;
    };

    std::shared_ptr<const TSPInformation> read_information(std::ifstream &ifd);

    std::ostream& operator<<(std::ostream& os, const TSPFile::TSPInformation &info);
};

#endif
