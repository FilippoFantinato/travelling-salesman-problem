#ifndef TSPCPXSOLVER_H
#define TSPCPXSOLVER_H

#include "TSPSolver.h"
#include "../../cpxmacro.h"

class TSPCPXSolver : public TSPSolver
{
protected:
    CEnv env;
    Prob lp;

    const std::string& name;

public:
    TSPCPXSolver(const TSP& tsp, const std::string& name);

    virtual void build() = 0;

    double solve() override;

    void write_file(const std::string& directory = "");

    void free();
};

// std::vector<double> varVals;
// varVals.resize(n_cols);
// CHECKED_CPX_CALL( CPXgetx, env, lp, &varVals[0], 0, n_cols - 1);
// for ( int i = 0 ; i < n_cols ; ++i ) {
// 	/// to read variables names the API function ``CPXgetcolname'' may be used (it is rather tricky, see the API manual if you like...)
// 	/// status = CPXgetcolname (env, lp, cur_colname, cur_colnamestore, cur_storespace, &surplus, 0, cur_numcols-1);
// 	std::cout << "var in position " << i << " : " << varVals[i] << std::endl;
// }

// const int N = tsp->get_n();
// int n_cols = CPXgetnumcols(env, lp);

// // if (n_cols != N*(N-1)) { 
// // 	throw std::runtime_error(std::string(__FILE__) + ":" + STRINGIZE(__LINE__) + ": " + "different number of variables"); 
// // }

#endif
