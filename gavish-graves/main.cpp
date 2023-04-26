#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
#include <unordered_set>

#include "../libraries/tspfile/tspfile.h"
#include "../libraries/utils/measure_time.h"
#include "gavish_graves.h"

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
			std::shared_ptr<TSPCPXSolver> solver(new GavishGraves(*tsp, info->name));


			double time = Utils::measure_time([&solver](){
				solver->solve();
			});
			double obj_value = solver->get_obj_value();

			std::cout << *info << std::endl << std::endl;
			std::cout << "Execution time: " << time << "s" << std::endl;
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
