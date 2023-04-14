#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
#include <unordered_set>

#include "gavish-graves.h"
#include "Coordinate.h"

int status;
char errmsg[BUF_SIZE];

void solve_tsp(CEnv env, Prob lp, const std::unique_ptr<TSP>& tsp) 
{
	const std::set<Vertex> vertices = tsp->get_vertices();
	const std::set<Edge *>& edges = tsp->get_edges();
	const int N = tsp->get_n();
	const Vertex IN = *(vertices.cbegin());

	std::map<Vertex, std::map<Vertex, int>> map_x;
	std::map<Vertex, std::map<Vertex, int>> map_y;

	long current_var = 0;

	// OBJ function
	// add y vars [in o.f.: sum[i, j] c_ij yij]
	for(auto edge: edges)
	{
		Vertex i = std::get<0>(*edge);
		Vertex j = std::get<1>(*edge);
		Weight w = std::get<2>(*edge);

		char type = 'B';
		double lb = 0.0;
		double ub = 1.0;
		char *yname = const_cast<char *>(("y_" + std::to_string(i) + "_" + std::to_string(j)).c_str());
		
		map_y[i][j] = current_var;
		++current_var;

		CHECKED_CPX_CALL(CPXnewcols, env, lp, 1, &w, &lb, &ub, &type, &yname);
	}

	// add x vars
	for(auto edge: edges)
	{
		Vertex i = std::get<0>(*edge);
		Vertex j = std::get<1>(*edge);

		if(j != IN) {
			char type = 'C';
			double lb = 0.0;
			double ub = CPX_INFBOUND;
			char *xname = const_cast<char *>(("x_" + std::to_string(i) + "_" + std::to_string(j)).c_str());
			double obj = 0;

			map_x[i][j] = current_var;
			++current_var;

			CHECKED_CPX_CALL(CPXnewcols, env, lp, 1, &obj, &lb, &ub, &type, &xname);
		}
	}

	// Constraints

	// for all k in N\{0}, sum[i] x_i_k - sum[j!=0] x_k_j = 1
	for(auto& k: vertices)
	{
		if(k != IN)
		{
			std::vector<int> idx;
			std::vector<double> coef;
			char sense = 'E';
			double rhs = 1;
			int matbeg = 0;

			for(auto& i: vertices)
			{
				if(tsp->exist_edge(i, k))
				{
					idx.push_back(map_x[i][k]);
					coef.push_back(1.0);
				}
			}

			for(auto& j: vertices)
			{
				if(j != IN && tsp->exist_edge(k, j))
				{
					idx.push_back(map_x[k][j]);
					coef.push_back(-1.0);
				}
			}

			CHECKED_CPX_CALL(CPXaddrows, env, lp, 0, 1, idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], NULL, NULL);
		}
	}

	// for all i in N, sum[j] y_i_j = 1
	for(auto& i: vertices)
	{
		std::vector<int> idx;
		std::vector<double> coef;
		char sense = 'E';
		int matbeg = 0;
		double rhs = 1;

		for(auto& j: vertices)
		{
			if(tsp->exist_edge(i, j))
			{
				idx.push_back(map_y[i][j]);
				coef.push_back(1.0);
			}
		}

		CHECKED_CPX_CALL( CPXaddrows, env, lp, 0, 1, idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], NULL, NULL);
	}

	// for all j in N, sum[i] y_i_j = 1
	for(auto& j: vertices)
	{
		std::vector<int> idx;
		std::vector<double> coef;
		char sense = 'E';
		int matbeg = 0;
		double rhs = 1;

		for(auto& i: vertices)
		{
			if(tsp->exist_edge(i, j))
			{
				idx.push_back(map_y[i][j]);
				coef.push_back(1.0);
			}
		}

		CHECKED_CPX_CALL( CPXaddrows, env, lp, 0, 1, idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], NULL, NULL);
	}

	// for all (i,j) in A, x_i_j <= (|N|-1) y_i_j
	for(auto edge: edges)
	{
		Vertex i = std::get<0>(*edge);
		Vertex j = std::get<1>(*edge);

		if(j != IN)
		{
			std::vector<int> idx{ map_x[i][j], map_y[i][j] };
			std::vector<double> coef{ 1.0, 1-((double)N) };
			char sense = 'L';
			double rhs = 0.0;
			int matbeg = 0;

			CHECKED_CPX_CALL(CPXaddrows, env, lp, 0, 1, idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], NULL, NULL);
		}
	}
}

int main(int argc, char const *argv[])
{
	std::string file = argv[1];
	std::ifstream ifd(file);

	if(ifd.is_open()) 
	{ 
		const std::unique_ptr<TSP> tsp = read_tsp_from_file(ifd);

		std::cout << *tsp << std::endl;

		try
		{
			// init
			DECL_ENV( env );
			DECL_PROB( env, lp );
			// setup LP
			solve_tsp(env, lp, tsp);
			// Debug
			CHECKED_CPX_CALL( CPXwriteprob, env, lp, "tsp.lp", NULL );
			// optimize
			CHECKED_CPX_CALL( CPXmipopt, env, lp );
			// print
			double objval;
			CHECKED_CPX_CALL( CPXgetobjval, env, lp, &objval );
			std::cout << "Objval: " << objval << std::endl;
			
			const int N = tsp->get_n();
			int n_cols = CPXgetnumcols(env, lp);
			
			// if (n_cols != N*(N-1)) { 
			// 	throw std::runtime_error(std::string(__FILE__) + ":" + STRINGIZE(__LINE__) + ": " + "different number of variables"); 
			// }

			std::vector<double> varVals;
			varVals.resize(n_cols);
			CHECKED_CPX_CALL( CPXgetx, env, lp, &varVals[0], 0, n_cols - 1);
			// for ( int i = 0 ; i < n_cols ; ++i ) {
			// 	/// to read variables names the API function ``CPXgetcolname'' may be used (it is rather tricky, see the API manual if you like...)
			// 	/// status = CPXgetcolname (env, lp, cur_colname, cur_colnamestore, cur_storespace, &surplus, 0, cur_numcols-1);
			// 	std::cout << "var in position " << i << " : " << varVals[i] << std::endl;
			// }

			CHECKED_CPX_CALL( CPXsolwrite, env, lp, "tsp.sol" );
			
			// free
			CPXfreeprob(env, &lp);
			CPXcloseCPLEX(&env);
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
