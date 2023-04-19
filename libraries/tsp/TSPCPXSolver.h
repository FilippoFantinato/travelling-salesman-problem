#ifndef TSPCPXSOLVER_H
#define TSPCPXSOLVER_H

#include "TSPSolver.h"
#include "../cpxmacro.h"

class TSPCPXSolver : public TSPSolver
{
private:
    const std::string& name;
    const bool debug;

public:
    TSPCPXSolver(const TSP& tsp, bool debug = false, const std::string& name = "") 
        : TSPSolver(tsp), debug(debug), name(name)
    {
        DECL_ENV(env);
        DECL_PROB(env, lp);
    }

    virtual void build() = 0;

    virtual double solve() override
    {
        build();
        
        CHECKED_CPX_CALL( CPXmipopt, env, lp );
        
        if(debug) CHECKED_CPX_CALL(CPXwriteprob, env, lp, (name + std::string(".lp")).c_str(), NULL);

        CHECKED_CPX_CALL(CPXsolwrite, env, lp, (name + std::string(".sol")).c_str());

        double objval;
        CHECKED_CPX_CALL(CPXgetobjval, env, lp, &objval);
        return objval;
    }

    void free()
    {
        CPXfreeprob(env, &lp);
        CPXcloseCPLEX(&env);
    }
};

// std::vector<double> varVals;
// varVals.resize(n_cols);
// CHECKED_CPX_CALL( CPXgetx, env, lp, &varVals[0], 0, n_cols - 1);
// for ( int i = 0 ; i < n_cols ; ++i ) {
// 	/// to read variables names the API function ``CPXgetcolname'' may be used (it is rather tricky, see the API manual if you like...)
// 	/// status = CPXgetcolname (env, lp, cur_colname, cur_colnamestore, cur_storespace, &surplus, 0, cur_numcols-1);
// 	std::cout << "var in position " << i << " : " << varVals[i] << std::endl;
// }

#endif
