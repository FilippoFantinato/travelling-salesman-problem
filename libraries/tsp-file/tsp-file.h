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

#include "TSPSection.h"
#include "TSPInformation.h"
#include "../tsp-readers/tsp-readers.h"
#include "../tsp-readers/types.h"

/*!
    \brief methods for reading a tsp instance and generate the corresponding tsp from it
*/
namespace TSPFile
{
    typedef std::shared_ptr<const TSP> (*TSPHandler)(std::ifstream &ifd, long dimension);
    typedef std::pair<std::shared_ptr<const TSPFile::TSPInformation>, std::shared_ptr<const TSP>> PairInformationTSP;

    /*!
        \brief init tsp from a file

        @param ifd: input stream of the file to read
    */
    PairInformationTSP init_tsp_from_file(std::ifstream &ifd);

    /*!
        \brief choose the function to use for reading the coordinates
               and generating the tsp according to the edge_weight_type,
               which states the cost function of a tsp instance

        @param info: object containing all information about a tsp instance
    */
    TSPHandler choose_tsp_handler(const TSPInformation& info);
}

#endif
