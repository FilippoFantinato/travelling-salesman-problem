#ifndef TSP_SOLVERS_TSP_CPX_SOLVER_H
#define TSP_SOLVERS_TSP_CPX_SOLVER_H

#include <vector>

#include "TSPSolver.h"
#include "cpxmacro.h"

/*!
    \brief superclass of all solvers exploiting CPLEX
*/
class TSPCPXSolver : public TSPSolver
{
protected:
    // objects describing the model
    Env env;
    Prob lp;

public:
    /*!
        \brief TSPCPXSolver class constructor

        @param tsp: tsp to solve
        @param name: tsp instance name
    */
    TSPCPXSolver(const TSP& tsp, const std::string& name);
    ~TSPCPXSolver() override;

    /*!
        \brief get the best solution cost
    */
    double get_solution_cost() const override;

    /*!
        \brief get all the vars in the model
    */
    std::shared_ptr<std::vector<double>> get_vars() const;

    /*!
        \brief get N_COLS vars in the model
    */
    std::shared_ptr<std::vector<double>> get_vars(size_t N_COLS) const;

    /*!
        \brief get the number of vars in the model
    */
    size_t get_n_vars() const;

    /*!
        \brief solve the tsp
    */
    double solve() override;

    /*!
        \brief build the model to be solved
    */
    virtual void build() = 0;

    /*!
        \brief get the best cycle
    */
    virtual std::shared_ptr<Path> get_best_cycle() const = 0;

    /*!
        \brief set a time limit to the running time
    */
    void set_time_limit(double time_limit);

    /*!
        \brief write in a given directory the models in a file with the same name
               as the one given in the constructor in the directory
    */
    void write_file(const std::string& directory) const;

    /*!
        \brief free the object env and lp
    */
    void free();
};

#endif
