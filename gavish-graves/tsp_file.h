#ifndef TSPFILE_H
#define TSPFILE_H

#include <set>
#include <memory>
#include <fstream>
#include <string>
#include "gavish_graves.h"


namespace TSPFile
{
    const std::smart_ptr<TSP> read_tsp_from_file(std::ifstream &ifd) 
    {
        std::smart_ptr<TSP> tsp = std::make_shared<TSP>();
        std::set<const std::pair<Vertex, Point *> *> points;

        int v = 0;
        while(ifd.good())
        {
            double x; double y;
            ifd >> x; ifd >> y;
            points.insert(new std::pair<Vertex, Point *>(v, new Point(x, y)));
            ++v;
        }

        for(auto it1 = points.cbegin(); it1 != points.cend();)
        {
            const Vertex v 	= (*it1)->first;
            const Point *p1 = (*it1)->second;
            ++it1;

            for(auto it2 = it1; it2 != points.cend(); ++it2)
            {
                const Vertex t 	= (*it2)->first;
                const Point *p2 = (*it2)->second;

                double d = euclidian_distance(*p1, *p2);
                tsp->add_edge(v, t, d);
                tsp->add_edge(t, v, d);
            }
        }

        return tsp;
    }
};

#endif TSPFILE_H

