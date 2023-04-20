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

        static EnumTSPSection to_enum(std::string s);
    };

    class EdgeWeightType
    {
    public:
        const static std::string euc2d;
        const static std::string geo_location;
        const static std::string explicit_matrix;
    };
};

#endif
