#include "full_matrix.h"

namespace TSPFile::FULL_MATRIX
{
    std::shared_ptr<const TSP> init_tsp(std::ifstream& ifd, int dimension)
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
};
