#ifndef TSPCPXSOLVER_H
#define TSPCPXSOLVER_H

#include <vector>

#include "./TSPSolver.h"
#include "cpxmacro.h"

class TSPCPXSolver : public TSPSolver
{
protected:
    CEnv env;
    Prob lp;

public:
    TSPCPXSolver(const TSP& tsp, const std::string& name);
    ~TSPCPXSolver() override;

    double get_solution_cost() const override;
    std::shared_ptr<std::vector<double>> get_vars() const;
    std::shared_ptr<std::vector<double>> get_vars(size_t N_COLS) const;
    size_t get_n_vars() const;

    double solve() override;
    virtual void build() = 0;
    virtual std::shared_ptr<Path> get_best_cycle() const = 0;

    void write_file(const std::string& directory) const;
    void free();
};

#endif
