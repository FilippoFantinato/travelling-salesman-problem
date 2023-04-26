#include "print.h"

namespace Utils
{
    void print_cli(const std::vector<double>& var_vals, const int N)
    {
        for(int i = 0; i <= N; ++i)
        {
            for(int j = 0; j <= N; ++j)
            {
                if(i == 0)
                {
                    if(j != 0)
                    {
                        std::cout << j;
                    }
                }
                else 
                {
                    if(j == 0)
                    {
                        std::cout << i;
                    }
                    else
                    {
                        if(i != j)
                        {
                            double w = var_vals[(i-1)*N+(j-1)];
                            std::cout << (w == 1 ? 1 : 0);
                        }
                        else
                        {
                            std::cout << "-";
                        }
                    }
                }
                std::cout << "\t";
            }
            std::cout << std::endl;
        }
    }
};

