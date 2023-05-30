#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
#include <unordered_set>

#include "../libraries/tsp-file/tsp-file.h"
#include "../libraries/utils/measure-time.h"
#include "../libraries/utils/print.h"
#include "LinKernighan.h"

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

		std::shared_ptr<LinKernighan> solver(new LinKernighan(*tsp, [](const TSP& tsp) -> std::vector<Vertex>* {
			const std::set<Vertex>& vertices = tsp.get_vertices();
			return new std::vector<Vertex>(vertices.cbegin(), vertices.cend());
		}));

		double time = Utils::measure_time([&solver](){
			solver->solve();
		});
		double obj_value = solver->get_solution_cost();
		// solver->write_file("out/");

		std::cout << *info << std::endl << std::endl;
		std::cout << "Execution time: " << time << "s" << std::endl;
		std::cout << "Object function value: " << obj_value << std::endl;

		// std::shared_ptr<std::vector<double>> var_vals = solver->get_vars(N*N-N);

		// Utils::print_cli(*var_vals, N);
	}
	else
	{
		std::cerr << "File " << file << " doesn't exist" << std::endl;
	}

	return 0;
}
