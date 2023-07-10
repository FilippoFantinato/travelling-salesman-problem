#include "tsp-readers.h"

namespace TSPReaders::FullMatrix
{
    std::shared_ptr<const TSP> init_tsp(std::ifstream& ifd, long dimension)
    {
        std::shared_ptr<TSP> tsp = std::make_shared<TSP>(dimension);
        
        for(int v = 0; v < dimension; ++v)
        {
            for(int t = 0; t < dimension; ++t)
            {
                double weight;
                ifd >> weight;
                
                if(v != t)
                {
                    tsp->add_edge(v, t, weight);
                }
            }
        }

        return tsp;
    }
}
