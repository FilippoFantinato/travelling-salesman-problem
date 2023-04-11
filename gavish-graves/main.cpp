#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <memory>
#include <unordered_set>

#include "Graph.h"
#include "Point.h"
#include "../libraries/cpxmacro.h"

typedef int Vertex;
typedef double Weight;
typedef std::tuple<Vertex, Vertex, Weight> Edge;

typedef Graph<Vertex, Weight> TSP;

int status;
char errmsg[BUF_SIZE];

double euclidian_distance(const Point &p1, const Point &p2)
{
	return sqrt(pow(p1.y - p2.y, 2) + pow(p1.x - p2.x, 2));
}

const std::shared_ptr<TSP> read_tsp_from_file(std::ifstream &ifd) 
{
	
	std::shared_ptr<TSP> tsp(new TSP());
	std::set<const std::pair<Vertex, Point *> *> points;

	int v = 0;
	while(ifd.good())
	{
		double x; double y;
		ifd >> x; ifd >> y;
		points.insert(new std::pair<Vertex, Point *>(v, new Point(x, y)));
		++v;
	}

	for(auto it1 = points.cbegin(); it1 != points.cend();)
	{
		const Vertex v = (*it1)->first;
		const Point *p1 = (*it1)->second;

		++it1;

		for(auto it2 = it1; it2 != points.cend(); ++it2)
		{
			const Vertex t = (*it2)->first;
			const Point *p2 = (*it2)->second;

			tsp->add_edge(v, t, euclidian_distance(*p1, *p2));
		}
	}

	return tsp;
}

void solve_tsp(CEnv env, Prob lp, std::shared_ptr<TSP> tsp) 
{
	const int NAME_SIZE = 512;
	char name[NAME_SIZE];

	std::shared_ptr<std::set<Vertex>> vertices = tsp->get_vertices();
	const int N = tsp->get_n();
	const Vertex IN = *(vertices->cbegin());

	std::map<Vertex, std::map<Vertex, int>> map_x;
	std::map<Vertex, std::map<Vertex, int>> map_y;

	int current_var = 0;
	
	// OBJ function

	// add y vars [in o.f.: sum[i, j] c_ij yij]
	for(auto i = vertices->cbegin(); i != vertices->cend();)
	{
		const Vertex v = *i; ++i;

		for(auto j = i; j != vertices->cend(); ++j)
		{
			const Vertex t = *j;

			char ytype = 'B';
			double lb = 0.0;
			double ub = 1.0;
			snprintf(name, NAME_SIZE, "y_%d_%d", v, t);
			char* yname = (char*)(&name[0]);
			double y_obj = tsp->get_weight(v, t);

			map_y[v][t] = current_var;
			map_y[t][v] = current_var;
			++current_var;

			CHECKED_CPX_CALL(CPXnewcols, env, lp, 1, &y_obj, &lb, &ub, &ytype, &yname);
		}
	}

	std::cout << N << " " << current_var << std::endl;

	// add x vars
	for(auto i = vertices->cbegin(); i != vertices->cend();)
	{
		const Vertex v = *i; ++i;

		for(auto j = i; j != vertices->cend(); ++j)
		{
			const Vertex t = *j;

			char xtype = 'R';
			double lb = 1.0;
			double ub = CPX_INFBOUND;
			snprintf(name, NAME_SIZE, "x_%d_%d", v, t);
			char* xname = (char*)(&name[0]);
			double obj = 0;

			map_x[v][t] = current_var;
			map_x[t][v] = current_var;
			++current_var;

			CHECKED_CPX_CALL(CPXnewcols, env, lp, 1, &obj, &lb, &ub, &xtype, &xname);
		}
	}

	// Constraints

	// for all k in N\{0}, sum[i] x_i_k - sum[j!=0] x_k_j = 1
	for(auto i = vertices->cbegin(); i != vertices->cend();)
	{
		const Vertex k = *i; ++i;

		if(k != IN) {
			std::vector<int> idx;
			std::vector<double> coef;
			char sense = 'E';
			double rhs = 1;
			int matbeg = 0;

			for(auto j = vertices->cbegin(); j != vertices->cend(); ++j) {
				const Vertex v = *j;

				idx.push_back(map_x[v][k]);
				coef.push_back(v == IN ? 1.0 : 2.0);
			}

			CHECKED_CPX_CALL( CPXaddrows, env, lp, 0, 1, idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], NULL, NULL);
		}
	}

	// // for all i in N, sum[j] y_i_j = 1
	// for(auto i = vertices->cbegin(); i != vertices->cend();)
	// {
	// 	const Vertex v = *i; ++i;

	// 	std::vector<int> idx;
	// 	std::vector<double> coef;
	// 	char sense = 'E';

	// 	for(auto j = i; j != vertices->cend(); ++j)
	// 	{
	// 		const Vertex t = *j; ++j;
	// 		idx.push_back(map_y[v][t]);
	// 		coef.push_back(1.0);
	// 	}
	// 	int matbeg = 0;
	// 	double rhs = 1;
	// 	CHECKED_CPX_CALL( CPXaddrows, env, lp, 0     , 1     , idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], NULL      , NULL      );
	// }

	// // for all j in N, sum[i] y_i_j = 1
	// for(auto j = vertices->cbegin(); j != vertices->cend();)
	// {
	// 	const Vertex v = *j; ++j;

	// 	std::vector<int> idx;
	// 	std::vector<double> coef;
	// 	char sense = 'E';

	// 	for(auto i = j; i != vertices->cend(); ++i)
	// 	{
	// 		const Vertex t = *i;
	// 		idx.push_back(map_y[v][t]);
	// 		coef.push_back(1.0);
	// 	}
	// 	int matbeg = 0;
	// 	double rhs = 1;
	// 	CHECKED_CPX_CALL( CPXaddrows, env, lp, 0     , 1     , idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], NULL      , NULL      );
	// }

	// // for all (i,j) in A, x_i_j <= (|N|-1) y_i_j
	// for(auto i = vertices->cbegin(); i != vertices->cend();)
	// {
	// 	const Vertex v = *i; ++i;

	// 	for(auto j = i; j != vertices->cend(); ++j)
	// 	{
	// 		const Vertex t = *j;
			
	// 		std::vector<int> idx{ map_x[v][t], map_x[t][v] };
	// 		std::vector<double> coef{ 1.0, 1-N };
	// 		char sense = 'L';
	// 		double rhs = 0;
	// 		int matbeg = 0;

	// 		CHECKED_CPX_CALL(CPXaddrows, env, lp, 0, 1, idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], 0, 0);
	// 	}
	// }
}

int main(int argc, char const *argv[])
{
	std::string file = argv[1];
	std::ifstream ifd(file);

	if(ifd.is_open()) 
	{ 
		const std::shared_ptr<TSP> tsp = read_tsp_from_file(ifd);

		// std::cout << *tsp << std::endl;

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
			// CHECKED_CPX_CALL( CPXmipopt, env, lp );
			// print
			// double objval;
			// CHECKED_CPX_CALL( CPXgetobjval, env, lp, &objval );
			// std::cout << "Objval: " << objval << std::endl;
			
			const int N = tsp->get_n();
			int n_cols = CPXgetnumcols(env, lp);
			
			if (n_cols != N*(N-1)) { 
				throw std::runtime_error(std::string(__FILE__) + ":" + STRINGIZE(__LINE__) + ": " + "different number of variables"); 
			}
			
			// std::vector<double> varVals;
			// varVals.resize(n);
			// CHECKED_CPX_CALL( CPXgetx, env, lp, &varVals[0], 0, n - 1 );
			/// status = CPXgetx (env, lp, x          , 0, CPXgetnumcols(env, lp)-1);
			// for ( int i = 0 ; i < n ; ++i ) {
			// 	/// to read variables names the API function ``CPXgetcolname'' may be used (it is rather tricky, see the API manual if you like...)
			// 	/// status = CPXgetcolname (env, lp, cur_colname, cur_colnamestore, cur_storespace, &surplus, 0, cur_numcols-1);
			// 	std::cout << "var in position " << i << " : " << varVals[i] << std::endl;
			// }

			// CHECKED_CPX_CALL( CPXsolwrite, env, lp, "tsp.sol" );
			
			// free
			CPXfreeprob(env, &lp);
			CPXcloseCPLEX(&env);
		}
		catch(std::exception& e)
		{
			std::cout << ">>>EXCEPTION: " << e.what() << std::endl;
		}
	
		ifd.close();
	}
	else
	{
		std::cout << "File " << file << " doesn't exist" << std::endl;
	}

	return 0;
}
