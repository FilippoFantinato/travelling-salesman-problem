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
        edge_weight_format,
        dimension,
        optimal_solution,
        node_coord_section, 
        edge_weight_section,
        eof,
        none_tsp_section
    };

    class TSPSection
    {
    public:
        const static std::string name;
        const static std::string comment;
        const static std::string type;
        const static std::string edge_weight_type;
        const static std::string edge_weight_format;
        const static std::string dimension;
        const static std::string optimal_solution;
        const static std::string node_coord_section;
        const static std::string edge_weight_section;
        const static std::string display_data_section;
        const static std::string eof;

        const static std::map<std::string, EnumTSPSection> string_to_enum;

        static EnumTSPSection to_enum(std::string s);
    };

    enum EnumEdgeWeightType
    {
        euc2d,
        geo_location,
        explicit_matrix, 
        none_edge_weight_type
    };

    class EdgeWeightType
    {
    public:
        const static std::string euc2d;
        const static std::string geo_location;
        const static std::string explicit_matrix;

        const static std::map<std::string, EnumEdgeWeightType> string_to_enum;

        static EnumEdgeWeightType to_enum(std::string s);
    };

    enum EnumEdgeWeightFormat
    {
        full_matrix,
        none_edge_weight_format
    };

    class EdgeWeightFormat
    {
    public:
        const static std::string full_matrix;

        const static std::map<std::string, EnumEdgeWeightFormat> string_to_enum;

        static EnumEdgeWeightFormat to_enum(std::string s);
    };
};

#endif
