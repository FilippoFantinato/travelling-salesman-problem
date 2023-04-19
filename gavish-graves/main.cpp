#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
#include <unordered_set>

#include "../libraries/tspfile/tspfile.h"
#include "gavish_graves.h"

int status;
char errmsg[BUF_SIZE];

void solve_tsp(CEnv env, Prob lp, std::shared_ptr<const TSP> tsp) 
{
	
}

int main(int argc, char const *argv[])
{
	std::string file = argv[1];
	std::ifstream ifd(file);

	if(ifd.is_open()) 
	{

		auto information_tsp = TSPFile::init_tsp_from_file(ifd);

		std::shared_ptr<const TSPFile::TSPInformation> info = information_tsp->first;
		std::shared_ptr<const TSP> tsp = information_tsp->second;

		try
		{
			// const int N = tsp->get_n();
			// int n_cols = CPXgetnumcols(env, lp);

			// // if (n_cols != N*(N-1)) { 
			// // 	throw std::runtime_error(std::string(__FILE__) + ":" + STRINGIZE(__LINE__) + ": " + "different number of variables"); 
			// // }
		}
		catch(const std::exception& e)
		{
			std::cerr << ">>>EXCEPTION: " << e.what() << std::endl;
		}
	}
	else
	{
		std::cerr << "File " << file << " doesn't exist" << std::endl;
	}

	return 0;
}
