#include "euc2d.h"

namespace TSPFile::EUC2D
{

    std::shared_ptr<const TSP> init_tsp(std::ifstream& ifd, int dimension)
    {
        return tsp_from_points(read_points(ifd, dimension));
    }

    std::shared_ptr<const VertexCoordinates> read_points(std::ifstream& ifd, int dimension)
    {
        VertexCoordinates points;

        for(int i = 0; i < dimension; ++i)
        {
            int v; double x; double y;
            ifd >> v; ifd >> x; ifd >> y;

            points.insert(
                std::make_shared<std::pair<Vertex, std::shared_ptr<Coordinate>>>(v, new Point(x, y))
            );
        }

        return std::make_shared<const VertexCoordinates>(points);
    }

    std::shared_ptr<const TSP> tsp_from_points(std::shared_ptr<const VertexCoordinates> coordinates)
    {
        std::shared_ptr<TSP> tsp = std::make_shared<TSP>();

        for(auto it1 = coordinates->cbegin(); it1 != coordinates->cend();)
        {
            const Vertex v 	= (*it1)->first;
            const Point &p1 = dynamic_cast<const Point&>(*((*it1)->second));
            ++it1;

            for(auto it2 = it1; it2 != coordinates->cend(); ++it2)
            {
                const Vertex t 	= (*it2)->first;
                const Point &p2 = dynamic_cast<const Point&>(*((*it2)->second));

                double d = round(p1.distance(p2));
                tsp->add_edge(v, t, d);
                tsp->add_edge(t, v, d);
            }
        }

        return tsp;
    }
};

