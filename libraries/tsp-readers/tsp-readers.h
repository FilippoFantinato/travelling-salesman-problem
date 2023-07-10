#ifndef TSP_TSP_READERS_H
#define TSP_TSP_READERS_H

#include <memory>
#include <vector>
#include <fstream>
#include <sstream>

#include "../tsp-readers/types.h"
#include "../coordinate/Coordinate.h"
#include "../coordinate/Point.h"
#include "../coordinate/ATTPoint.h"
#include "../coordinate/GeoLocation.h"

namespace TSPReaders
{
    /*!
        \brief generate tsp from a set of coordinates

        @param coordinates: set of coordinates from which generating the tsp
        @return the complete graph (tsp) generated starting from the set of coordinates
    */
    std::shared_ptr<const TSP> tsp_from_coordinates(const VertexCoordinates& coordinates);

    namespace ATT
    {
        std::shared_ptr<const TSP> init_tsp(std::ifstream& ifd, long dimension);
        std::shared_ptr<const VertexCoordinates> read_coordinates(std::ifstream& ifd, long dimension);
    }

    namespace EUC2D
    {
        std::shared_ptr<const TSP> init_tsp(std::ifstream& ifd, long dimension);
        std::shared_ptr<const VertexCoordinates> read_coordinates(std::ifstream& ifd, long dimension);
    }

    namespace Geo
    {
        std::shared_ptr<const TSP> init_tsp(std::ifstream& ifd, long dimension);
        std::shared_ptr<const VertexCoordinates> read_coordinates(std::ifstream& ifd, long dimension);
    }

    namespace FullMatrix
    {
        std::shared_ptr<const TSP> init_tsp(std::ifstream &ifd, long dimension);
    }

    namespace UpperRow
    {
        std::shared_ptr<const TSP> init_tsp(std::ifstream& ifd, long dimension);
    }
}

#endif
