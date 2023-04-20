#include "TSPCPXSolver.h"

TSPCPXSolver::TSPCPXSolver(const TSP& tsp, const std::string& name) 
    : TSPSolver(tsp), name(name)
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

    write_file("out/");

    double objval;
    CHECKED_CPX_CALL(CPXgetobjval, env, lp, &objval);
    
    return objval;
}

void TSPCPXSolver::write_file(const std::string& directory)
{
    std::string path = directory + name;

    CHECKED_CPX_CALL(CPXwriteprob, env, lp, (path + std::string(".lp")).c_str(), NULL);
    CHECKED_CPX_CALL(CPXsolwrite, env, lp, (path + std::string(".sol")).c_str());
}


void TSPCPXSolver::free()
{
    // CPXfreeprob(env, &lp);
    // CPXcloseCPLEX(&env);
}
