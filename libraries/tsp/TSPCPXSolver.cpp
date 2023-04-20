#include "TSPCPXSolver.h"

int status;
char errmsg[BUF_SIZE];

TSPCPXSolver::TSPCPXSolver(const TSP& tsp, bool debug, const std::string& name) : TSPSolver(tsp), debug(debug), name(name)
{
    this->env = CPXopenCPLEX(&status);
    if (status){
        CPXgeterrorstring(NULL, status, errmsg);
        int trailer = std::strlen(errmsg) - 1;
        if (trailer >= 0) errmsg[trailer] = '\0';
        throw std::runtime_error(std::string(__FILE__) + ":" + STRINGIZE(__LINE__) + ": " + errmsg);
    }

    this->lp = CPXcreateprob(env, &status, "");
    if (status){
        CPXgeterrorstring(NULL, status, errmsg);
        int trailer = std::strlen(errmsg) - 1;
        if (trailer >= 0) errmsg[trailer] = '0';
        throw std::runtime_error(std::string(__FILE__) + ":" + STRINGIZE(__LINE__) + ": " + errmsg);
    }
}


double TSPCPXSolver::solve()
{
    build();
    
    CHECKED_CPX_CALL( CPXmipopt, env, lp );
    
    if(debug) CHECKED_CPX_CALL(CPXwriteprob, env, lp, (name + std::string(".lp")).c_str(), NULL);

    CHECKED_CPX_CALL(CPXsolwrite, env, lp, (name + std::string(".sol")).c_str());

    double objval;
    CHECKED_CPX_CALL(CPXgetobjval, env, lp, &objval);
    return objval;
}
