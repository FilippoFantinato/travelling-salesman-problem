#ifndef TSPFILE_EUC2D_H
#define TSPFILE_EUC2D_H

#include <memory>
#include <sstream>

#include "TSPSection.h"
#include "types.h"
#include "../tsp/tsp.h"
#include "../coordinate/Coordinate.h"

namespace TSPFile::EUC2D
{
    std::shared_ptr<const VertexCoordinates> read_points(std::ifstream& ifd)
    {
        bool not_eof_met = true;
        VertexCoordinates points;

        std::string line;
        while(not_eof_met && getline(ifd, line))
        {
            Utils::trim(line);

            not_eof_met = line.compare(TSPSection::eof) != 0;

            if(not_eof_met)
            {
                std::stringstream ss(line);
                
                int v; double x; double y;
                ss >> v; ss >> x; ss >> y;

                points.insert(
                    std::make_shared<std::pair<Vertex, std::shared_ptr<Coordinate>>>(v, new Point(x, y))
                );
            }
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

                double d = p1.distance(p2);
                tsp->add_edge(v, t, d);
                tsp->add_edge(t, v, d);
            }
        }

        return tsp;
    }

    std::shared_ptr<const TSP> init_tsp(std::ifstream& ifd)
    {
        return tsp_from_points(read_points(ifd));
    }
};

#endif
