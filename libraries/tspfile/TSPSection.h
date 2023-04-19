#ifndef TSPSECTION_H
#define TSPSECTION_H

#include <string>
#include <map>

namespace TSPFile
{
    enum EnumTSPSection
    {
        name, 
        comment,
        type, 
        edge_weight_type, 
        dimension,
        optimal_solution,
        node_coord_section, 
        eof,
        none
    };

    class TSPSection
    {
    public:
        const static std::string name;
        const static std::string comment;
        const static std::string type;
        const static std::string edge_weight_type;
        const static std::string dimension;
        const static std::string optimal_solution;
        const static std::string node_coord_section;
        const static std::string eof;

        const static std::map<std::string, EnumTSPSection> string_to_enum;

        static EnumTSPSection to_enum(std::string s) {
            try
            {
                return TSPSection::string_to_enum.at(s);
            }
            catch(const std::exception& e)
            {
                return EnumTSPSection::none;
            }
        }
    };

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

    class EdgeWeightType
    {
    public:
        const static std::string euc2d;
        const static std::string geo_location;
        const static std::string explicit_matrix;
    };

    const std::string EdgeWeightType::euc2d = "EUC_2D";
    const std::string EdgeWeightType::geo_location = "GEO";
    const std::string EdgeWeightType::explicit_matrix = "EXPLICIT";
};

#endif
