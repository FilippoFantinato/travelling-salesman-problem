#include "tsp-file.h"

namespace TSPFile
{
    PairInformationTSP init_tsp_from_file(std::ifstream &ifd)
    {
        std::shared_ptr<const TSPInformation> info = read_information(ifd);
        auto handler = choose_tsp_handler(*info);
        std::shared_ptr<const TSP> tsp = handler(ifd, info->dimension);

        return {info, tsp};
    }

    TSPHandler choose_tsp_handler(const TSPInformation& info)
    {
        switch (EdgeWeightType::to_enum(info.edge_weight_type))
        {
        case EnumEdgeWeightType::euc2d:
            return TSPFile::EUC2D::init_tsp;

        case EnumEdgeWeightType::geo_location:
            return TSPFile::GEO::init_tsp;

        case EnumEdgeWeightType::att:
            return TSPFile::ATT::init_tsp;

        case EnumEdgeWeightType::explicit_matrix:

            switch (EdgeWeightFormat::to_enum(info.edge_weight_format))
            {
            case EnumEdgeWeightFormat::full_matrix:
                return TSPFile::FULL_MATRIX::init_tsp;

            case EnumEdgeWeightFormat::upper_row:
                return TSPFile::UPPER_ROW::init_tsp;
            
            default:
                throw EdgeWeightNotHandled(info.edge_weight_format);
            }

        default:
            throw EdgeWeightNotHandled(info.edge_weight_type);
        }
    }
}

