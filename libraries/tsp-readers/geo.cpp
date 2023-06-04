#include "geo.h"

namespace TSPFile::GEO
{
    std::shared_ptr<const TSP> init_tsp(std::ifstream& ifd, int dimension)
    {
        return Utils::tsp_from_coordinates(*read_coordinates(ifd, dimension));
    }

    std::shared_ptr<const VertexCoordinates> read_coordinates(std::ifstream& ifd, int dimension)
    {
        VertexCoordinates coordinates;

        for(int i = 0; i < dimension; ++i)
        {
            int v; double x; double y;
            ifd >> v; ifd >> x; ifd >> y;

            coordinates.insert(
                std::make_shared<std::pair<Vertex, std::shared_ptr<Coordinate>>>(i, new GeoLocation(x, y))
            );
        }

        return std::make_shared<const VertexCoordinates>(coordinates);
    }
}
