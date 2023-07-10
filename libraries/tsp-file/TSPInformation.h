#ifndef TSP_TSP_INFORMATION_H
#define TSP_TSP_INFORMATION_H

#include <iostream>
#include <string>
#include <map>
#include <exception>
#include <memory>
#include <limits>
#include <fstream>

#include "TSPSection.h"
#include "../exceptions/IncompleteTSPFile.h"
#include "../utils/utils.h"

/*!
    \brief struct and methods for handling information read from a tsp instance
*/
namespace TSPFile
{
    struct TSPInformation
    {
        std::string name;
        std::string comment;
        std::string type;
        std::string edge_weight_type;
        std::string edge_weight_format;
        long dimension;
        double optimal_solution = std::numeric_limits<double>::quiet_NaN();
    };

    /*!
        \brief read all information, e.g. name, dimension, type, etc.
               from a tsp instance

        @param ifd: input stream of the file to read
    */
    std::shared_ptr<const TSPInformation> read_information(std::ifstream &ifd);

    std::ostream& operator<<(std::ostream& os, const TSPFile::TSPInformation &info);
}

#endif
