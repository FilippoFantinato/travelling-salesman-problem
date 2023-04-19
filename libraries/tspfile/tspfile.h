#ifndef TSPFILE_H
#define TSPFILE_H

#include <iostream>
#include <set>
#include <memory>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>

#include "../tsp/exceptions.h"

#include "types.h"
#include "TSPSection.h"
#include "TSPInformation.h"
#include "euc2d.h"
#include "geo_location.h"

namespace TSPFile
{
    typedef std::shared_ptr<const TSP> (*TSPHandler)(std::ifstream &ifd);
    typedef std::pair<std::shared_ptr<const TSPInformation>, std::shared_ptr<const TSP>> InformationTSP;

    std::shared_ptr<InformationTSP> init_tsp_from_file(std::ifstream &ifd)
    {
        std::shared_ptr<const TSPInformation> info = read_information(ifd);

        std::map<std::string, TSPHandler> weight_type_to_handler = {
            {EdgeWeightType::euc2d, &TSPFile::EUC2D::init_tsp},
            {EdgeWeightType::geo_location, &TSPFile::GEO::init_tsp}
        };

        try
        {
            auto handler = weight_type_to_handler.at(info->edge_weight_type);
            std::shared_ptr<const TSP> tsp = handler(ifd);

            return std::make_shared<InformationTSP>(info, tsp);
        }
        catch (const std::out_of_range &e)
        {
            throw EdgeWeightTypeNotHandled(info->edge_weight_type);
        }
    }
};

#endif
