#include <iostream>
#include <vector>
#include <memory>

#include "../libraries/tsp-file/tsp-file.h"
#include "../libraries/utils/measure-time.h"
#include "../libraries/utils/print.h"
#include "GavishGraves.h"

int main(int argc, char const *argv[])
{
	const std::string file = argv[1];
	std::ifstream ifd(file);

	if(ifd.is_open())
	{
		std::shared_ptr<const TSPFile::PairInformationTSP> information_tsp = TSPFile::init_tsp_from_file(ifd);

		std::shared_ptr<const TSPFile::TSPInformation> info = information_tsp->first;
		std::shared_ptr<const TSP> tsp = information_tsp->second;

		const int N = tsp->get_n();

		try
		{
			std::shared_ptr<TSPCPXSolver> solver(new GavishGraves(*tsp, info->name));

			double time = Utils::measure_time([&solver](){
				solver->solve();
			});
			double obj_value = solver->get_solution_cost();
//			solver->write_file("out/");

			std::cout << *info << std::endl << std::endl;
			std::cout << "Execution time: " << time << "s" << std::endl;
			std::cout << "Object function value: " << obj_value << std::endl;

			std::shared_ptr<std::vector<double>> var_vals = solver->get_vars(N*N-N);

			// Utils::print_cli(*var_vals, N);
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
