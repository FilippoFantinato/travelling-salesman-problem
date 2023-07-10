#ifndef TSP_SOLVERS_TSP_SOLVER_H
#define TSP_SOLVERS_TSP_SOLVER_H

#include "../tsp/tsp.h"
#include "../path/path.h"

/*!
    \brief superclass of all solvers
*/
class TSPSolver
{
protected:
    const TSP& tsp;
    const std::string& name;

public:
    /*!
        \brief TSPSolver class constructor

        @param tsp: tsp to solve
        @param name: tsp instance name
    */
    TSPSolver(const TSP& tsp, const std::string& name);
    virtual ~TSPSolver() = default;

    /*!
        \brief solve the tsp

        @return the best solution cost
    */
    virtual double solve() = 0;

    /*!
        \brief get the best cycle
    */
    virtual std::shared_ptr<Path> get_best_cycle() const = 0;

    /*!
        \brief get the best solution cost
    */
    virtual double get_solution_cost() const = 0;
};

#endif
