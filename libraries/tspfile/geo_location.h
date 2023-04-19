#ifndef TSPFILE_GEO_LOCATION_H
#define TSPFILE_GEO_LOCATION_H

#include <memory>
#include <sstream>

#include "TSPSection.h"
#include "types.h"
#include "../tsp/tsp.h"
#include "../coordinate/Coordinate.h"

namespace TSPFile::GEO
{
    std::shared_ptr<const VertexCoordinates> read_coordinates(std::ifstream& ifd)
    {
        VertexCoordinates geolocations;

        std::string line;
        while(getline(ifd, line) && (line.compare(TSPSection::eof) != 0))
        {
            std::stringstream ss(line);

            int v; double x; double y;
            ss >> v; ss >> x; ss >> y;

            geolocations.insert(
                std::make_shared<std::pair<Vertex, std::shared_ptr<Coordinate>>>(v, new GeoLocation(x, y))
            );
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

    std::shared_ptr<const TSP> init_tsp(std::ifstream& ifd)
    {
        return tsp_from_coordinates(read_coordinates(ifd));
    }
};

#endif
