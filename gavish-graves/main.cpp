#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
#include <unordered_set>

#include "../libraries/tspfile/tspfile.h"
#include "gavish_graves.h"
#include "gavish_graves_symmetric.h"

int main(int argc, char const *argv[])
{
	const std::string file = argv[1];
	std::ifstream ifd(file);

	if(ifd.is_open())
	{
		std::shared_ptr<const TSPFile::PairInformationTSP> information_tsp = TSPFile::init_tsp_from_file(ifd);

		std::shared_ptr<const TSPFile::TSPInformation> info = information_tsp->first;
		std::shared_ptr<const TSP> tsp = information_tsp->second;

		try
		{
			std::shared_ptr<TSPSolver> solver(new GavishGraves(*tsp, info->name));

			std::cout << *info << std::endl;

			double obj_value = solver->solve();
			// std::cout << *tsp << std::endl;
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
