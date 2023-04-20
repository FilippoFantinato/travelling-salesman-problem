#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
#include <unordered_set>

#include "../libraries/tspfile/tspfile.h"
#include "gavish_graves.h"

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
			std::shared_ptr<TSPSolver> solver(new GavishGraves(*tsp, true, info->name));

			double obj_value = solver->solve();

			// std::cout << *info << std::endl;
			std::cout << "Object function value: " << obj_value << std::endl;
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
