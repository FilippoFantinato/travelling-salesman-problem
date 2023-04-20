#include "geo.h"

namespace TSPFile::GEO
{
    std::shared_ptr<const TSP> init_tsp(std::ifstream& ifd, int dimension)
    {
        return tsp_from_coordinates(read_coordinates(ifd, dimension));
    }

    std::shared_ptr<const VertexCoordinates> read_coordinates(std::ifstream& ifd, int dimension)
    {
        VertexCoordinates geolocations;

        for(int i = 0; i < dimension; ++i)
        {
            int v; double x; double y;
            ifd >> v; ifd >> x; ifd >> y;

            std::cout << v << ": " << "(" << x << ", " << y << ")" << std::endl;

            geolocations.insert(
                std::make_shared<std::pair<Vertex, std::shared_ptr<Coordinate>>>(v, new GeoLocation(x, y))
            );
        }

        for(auto geolocation: geolocations)
        {
            auto geo = dynamic_cast<const GeoLocation&>(*(geolocation->second));
            std::cout << geolocation->first << ": " << "(" << geo.longitude << ", " << geo.latitude << ")" << std::endl;
        }

        return std::make_shared<const VertexCoordinates>(geolocations);
    }

    std::shared_ptr<const TSP> tsp_from_coordinates(std::shared_ptr<const VertexCoordinates> coordinates)
    {
        std::shared_ptr<TSP> tsp = std::make_shared<TSP>();

        for(auto it1 = coordinates->cbegin(); it1 != coordinates->cend();)
        {
            const Vertex v 	= (*it1)->first;
            const GeoLocation &geo1 = dynamic_cast<const GeoLocation&>(*((*it1)->second));
            ++it1;

            for(auto it2 = it1; it2 != coordinates->cend(); ++it2)
            {
                const Vertex t 	= (*it2)->first;
                const GeoLocation &geo2 = dynamic_cast<const GeoLocation&>(*((*it2)->second));

                double d = geo1.distance(geo2);
                tsp->add_edge(v, t, d);
                tsp->add_edge(t, v, d);
            }
        }

        return tsp;
    }
};
