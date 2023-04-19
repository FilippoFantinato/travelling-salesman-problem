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

    std::ostream &operator<<(std::ostream &os, const TSPInformation &info)
    {
        os << "NAME: " << info.name << std::endl;
        os << "COMMENT: " << info.comment << std::endl;
        os << "TYPE: " << info.type << std::endl;
        os << "EDGE_WEIGHT_TYPE: " << info.edge_weight_type << std::endl;
        os << "DIMENSION: " << info.dimension << std::endl;
        os << "OPTIMAL_SOLUTION: ";
        if (info.optimal_solution != -1)
        {
            os << info.optimal_solution;
        }
        else
        {
            os << "N/A";
        }

        return os;
    }

    std::shared_ptr<const TSPInformation> read_information(std::ifstream &ifd)
    {
        const std::string delimiter = ":";

        TSPInformation info;

        bool not_node_coord_section_met = true;

        std::string line;
        while (not_node_coord_section_met && getline(ifd, line))
        {
            Utils::trim(line);
            not_node_coord_section_met = line.compare(TSPSection::node_coord_section) != 0;

            if (not_node_coord_section_met)
            {
                std::string section = Utils::trim_copy(line.substr(0, line.find(delimiter)));
                std::string value = Utils::trim_copy(line.substr(line.find(delimiter) + 1));

                switch (TSPSection::to_enum(section))
                {
                case EnumTSPSection::name:
                    info.name = value;
                    break;
                case EnumTSPSection::comment:
                    info.comment = value;
                    break;
                case EnumTSPSection::type:
                    info.type = value;
                    break;
                case EnumTSPSection::edge_weight_type:
                    info.edge_weight_type = value;
                    break;
                case EnumTSPSection::dimension:
                    info.dimension = std::atoi(value.c_str());
                    break;
                case EnumTSPSection::optimal_solution:
                    info.optimal_solution = std::atoi(value.c_str());
                    break;
                default:
                    break;
                }
            }
        }

        if (not_node_coord_section_met) throw IncompleteTSPFile(TSPSection::node_coord_section);

        return std::make_shared<const TSPInformation>(info);
    }
};

#endif
