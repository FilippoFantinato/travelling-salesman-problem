#include "TSPSection.h"

namespace TSPFile
{
    const std::string TSPSection::name = "NAME";
    const std::string TSPSection::comment = "COMMENT";
    const std::string TSPSection::type = "TYPE";
    const std::string TSPSection::edge_weight_type = "EDGE_WEIGHT_TYPE";
    const std::string TSPSection::dimension = "DIMENSION";
    const std::string TSPSection::optimal_solution = "OPTIMAL_SOLUTION";
    const std::string TSPSection::node_coord_section = "NODE_COORD_SECTION";
    const std::string TSPSection::eof = "EOF";

    const std::map<std::string, EnumTSPSection> TSPSection::string_to_enum = {
        {TSPSection::name, EnumTSPSection::name},
        {TSPSection::comment, EnumTSPSection::comment},
        {TSPSection::type, EnumTSPSection::type},
        {TSPSection::edge_weight_type, EnumTSPSection::edge_weight_type},
        {TSPSection::dimension, EnumTSPSection::dimension},
        {TSPSection::optimal_solution, EnumTSPSection::optimal_solution},
        {TSPSection::node_coord_section, EnumTSPSection::node_coord_section},
        {TSPSection::eof, EnumTSPSection::eof}
    };

    EnumTSPSection TSPSection::to_enum(std::string s) 
    {
        try
        {
            return TSPSection::string_to_enum.at(s);
        }
        catch(const std::exception& e)
        {
            return EnumTSPSection::none;
        }
    }

    const std::string EdgeWeightType::euc2d = "EUC_2D";
    const std::string EdgeWeightType::geo_location = "GEO";
    const std::string EdgeWeightType::explicit_matrix = "EXPLICIT";
};

