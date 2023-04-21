#include "upper_row.h"

namespace TSPFile::UPPER_ROW
{
    std::shared_ptr<const TSP> init_tsp(std::ifstream& ifd, int dimension)
    {
        std::shared_ptr<TSP> tsp = std::make_shared<TSP>();

        for(int v = 1; v <= dimension; ++v)
        {
            for(int t = v + 1; t <= dimension; ++t)
            {
                double weight;
                ifd >> weight;

                tsp->add_edge(v, t, weight);
                tsp->add_edge(t, v, weight);
            }
        }

        return tsp;
    }
};

