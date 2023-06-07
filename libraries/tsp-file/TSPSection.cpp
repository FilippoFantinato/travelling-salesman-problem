#include "TSPSection.h"

namespace TSPFile
{
    // TSPSection
    const std::string TSPSection::name = "NAME";
    const std::string TSPSection::comment = "COMMENT";
    const std::string TSPSection::type = "TYPE";
    const std::string TSPSection::edge_weight_type = "EDGE_WEIGHT_TYPE";
    const std::string TSPSection::edge_weight_format = "EDGE_WEIGHT_FORMAT";
    const std::string TSPSection::dimension = "DIMENSION";
    const std::string TSPSection::optimal_solution = "OPTIMAL_SOLUTION";
    const std::string TSPSection::node_coord_section = "NODE_COORD_SECTION";
    const std::string TSPSection::edge_weight_section = "EDGE_WEIGHT_SECTION";
    const std::string TSPSection::display_data_section = "DISPLAY_DATA_SECTION";
    const std::string TSPSection::eof = "EOF";

    const std::map<std::string, EnumTSPSection> TSPSection::string_to_enum = {
        {TSPSection::name, EnumTSPSection::name},
        {TSPSection::comment, EnumTSPSection::comment},
        {TSPSection::type, EnumTSPSection::type},
        {TSPSection::dimension, EnumTSPSection::dimension},
        {TSPSection::optimal_solution, EnumTSPSection::optimal_solution},
        {TSPSection::edge_weight_type, EnumTSPSection::edge_weight_type},
        {TSPSection::edge_weight_format, EnumTSPSection::edge_weight_format},
        {TSPSection::node_coord_section, EnumTSPSection::node_coord_section},
        {TSPSection::edge_weight_section, EnumTSPSection::edge_weight_section},
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
            return EnumTSPSection::none_tsp_section;
        }
    }

    // EdgeWeightType
    const std::string EdgeWeightType::euc2d = "EUC_2D";
    const std::string EdgeWeightType::geo_location = "GEO";
    const std::string EdgeWeightType::att = "ATT";
    const std::string EdgeWeightType::explicit_matrix = "EXPLICIT";

    const std::map<std::string, EnumEdgeWeightType> EdgeWeightType::string_to_enum = {
        {EdgeWeightType::euc2d, EnumEdgeWeightType::euc2d},
        {EdgeWeightType::geo_location, EnumEdgeWeightType::geo_location},
        {EdgeWeightType::att, EnumEdgeWeightType::att},
        {EdgeWeightType::explicit_matrix, EnumEdgeWeightType::explicit_matrix}
    };

    EnumEdgeWeightType EdgeWeightType::to_enum(std::string s) 
    {
        try
        {
            return EdgeWeightType::string_to_enum.at(s);
        }
        catch(const std::exception& e)
        {
            return EnumEdgeWeightType::none_edge_weight_type;
        }
    }

    // EdgeWeightFormat
    const std::string EdgeWeightFormat::full_matrix = "FULL_MATRIX";
    const std::string EdgeWeightFormat::upper_row = "UPPER_ROW";

    const std::map<std::string, EnumEdgeWeightFormat> EdgeWeightFormat::string_to_enum = {
        {EdgeWeightFormat::full_matrix, EnumEdgeWeightFormat::full_matrix},
        {EdgeWeightFormat::upper_row, EnumEdgeWeightFormat::upper_row}
    };

    EnumEdgeWeightFormat EdgeWeightFormat::to_enum(std::string s) 
    {
        try
        {
            return EdgeWeightFormat::string_to_enum.at(s);
        }
        catch(const std::exception& e)
        {
            return EnumEdgeWeightFormat::none_edge_weight_format;
        }
    }
}
