#include "TSPCPXSolver.h"

TSPCPXSolver::TSPCPXSolver(const TSP& tsp, const std::string& name) 
    : TSPSolver(tsp, name)
{
    this->env = CPXopenCPLEX(&status);
    if (status){
        CPXgeterrorstring(nullptr, status, errmsg);
        int trailer = std::strlen(errmsg) - 1;
        if (trailer >= 0) errmsg[trailer] = '\0';
        throw std::runtime_error(std::string(__FILE__) + ":" + STRINGIZE(__LINE__) + ": " + errmsg);
    }

    this->lp = CPXcreateprob(env, &status, "");
    if (status){
        CPXgeterrorstring(nullptr, status, errmsg);
        int trailer = std::strlen(errmsg) - 1;
        if (trailer >= 0) errmsg[trailer] = '0';
        throw std::runtime_error(std::string(__FILE__) + ":" + STRINGIZE(__LINE__) + ": " + errmsg);
    }
}

TSPCPXSolver::~TSPCPXSolver()
{
    free();
}

double TSPCPXSolver::get_solution_cost() const
{
    double obj_value;
    CHECKED_CPX_CALL(CPXgetobjval, env, lp, &obj_value);

    return obj_value;
}

std::shared_ptr<std::vector<double>> TSPCPXSolver::get_vars(size_t N_COLS) const
{
    std::vector<double> var_vals(N_COLS, 0);

    CHECKED_CPX_CALL(CPXgetx, env, lp, &var_vals[0], 0, N_COLS - 1);
    
    return std::make_shared<std::vector<double>>(var_vals);
}

std::shared_ptr<std::vector<double>> TSPCPXSolver::get_vars() const
{
    size_t N_COLS = get_n_vars();
    return get_vars(N_COLS);
}

size_t TSPCPXSolver::get_n_vars() const
{
    return CPXgetnumcols(env, lp);
}

double TSPCPXSolver::solve()
{
    build();
    CHECKED_CPX_CALL(CPXmipopt, env, lp);

    return get_solution_cost();
}

void TSPCPXSolver::write_file(const std::string& directory) const
{
    std::string path = directory + name;

    CHECKED_CPX_CALL(CPXwriteprob, env, lp, (path + std::string(".lp")).c_str(), nullptr);
    CHECKED_CPX_CALL(CPXsolwrite, env, lp, (path + std::string(".sol")).c_str());
}

void TSPCPXSolver::free()
{
     CPXfreeprob(env, &lp);
     CPXcloseCPLEX(const_cast<CPXENVptr *>(&env));
}
