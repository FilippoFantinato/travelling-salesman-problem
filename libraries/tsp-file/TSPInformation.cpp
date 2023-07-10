#include "TSPInformation.h"

namespace TSPFile
{
    std::shared_ptr<const TSPInformation> read_information(std::ifstream &ifd)
    {
        const std::string delimiter = ":";

        TSPInformation info;

        bool not_node_coord_section_met = true;
        bool not_edge_weight_section_met = true;

        std::string line;
        while (not_edge_weight_section_met && not_node_coord_section_met && getline(ifd, line))
        {
            Utils::trim(line);
            not_node_coord_section_met = line != TSPSection::node_coord_section;
            not_edge_weight_section_met = line != TSPSection::edge_weight_section;


            if (not_node_coord_section_met && not_edge_weight_section_met)
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
                case EnumTSPSection::edge_weight_format:
                    info.edge_weight_format = value;
                    break;
                case EnumTSPSection::dimension:
                    info.dimension = std::strtol(value.c_str(), nullptr, 10);
                    break;
                case EnumTSPSection::optimal_solution:
                    info.optimal_solution = std::stod(value);
                    break;
                default:
                    break;
                }
            }
        }

        if (not_node_coord_section_met && not_edge_weight_section_met)
        {
            throw IncompleteTSPFile(TSPSection::node_coord_section);
        }

        return std::make_shared<const TSPInformation>(info);
    }

    std::ostream& operator<<(std::ostream& os, const TSPFile::TSPInformation &info)
    {
        os << "NAME: " << info.name << std::endl;
        
        if(!info.comment.empty())
        {
            os << "COMMENT: " << info.comment << std::endl;
        }

        os << "TYPE: " << info.type << std::endl;
        os << "EDGE_WEIGHT_TYPE: " << info.edge_weight_type << std::endl;
        
        if(!info.edge_weight_format.empty())
        {
            os << "EDGE_WEIGHT_FORMAT: " << info.edge_weight_format << std::endl;
        }
        
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
}
