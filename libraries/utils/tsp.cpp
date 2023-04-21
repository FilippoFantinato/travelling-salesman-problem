#include "tsp.h"

namespace Utils
{
    std::shared_ptr<const TSP> tsp_from_coordinates(std::shared_ptr<const TSPFile::VertexCoordinates> coordinates)
    {
        std::shared_ptr<TSP> tsp = std::make_shared<TSP>();

        for(auto it1 = coordinates->cbegin(); it1 != coordinates->cend();)
        {
            const Vertex v 	= (*it1)->first;
            const Coordinate &p1 = *((*it1)->second);
            ++it1;

            for(auto it2 = it1; it2 != coordinates->cend(); ++it2)
            {
                const Vertex t 	= (*it2)->first;
                const Coordinate &p2 = *((*it2)->second);

                double d = p1.distance(p2);
                tsp->add_edge(v, t, d);
                tsp->add_edge(t, v, d);
            }
        }

        return tsp;
    }
};

