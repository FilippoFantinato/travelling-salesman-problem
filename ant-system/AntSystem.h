#ifndef TSP_ANT_SYSTEM_H
#define TSP_ANT_SYSTEM_H

#include <cmath>
#include <iterator>
#include <future>
#include <thread>

#include "../libraries/path/path.h"
#include "../libraries/tsp-solvers/TSPSolver.h"
#include "../libraries/utils/utils.h"

typedef std::pair<std::shared_ptr<Path>, double> PairPathCost;

/*!
    \brief Ant System metaheuristic
*/
class AntSystem : public TSPSolver
{
private:
    const double iterations;
    const double n_ants;
    const double alpha;
    const double beta;
    const double Q;
    const double rho;

    std::unique_ptr<std::unique_ptr<double[]>[]> intensity;

    PairPathCost best_cycle_cost;

    /*!
        \brief Method which builds a solution (cycle) starting from a source_node

        @param source_node: node from which to start the ant
        @return the solution discovered by that ant with its cost
    */
    PairPathCost ant(Vertex source_node) const;

    /*!
        \brief Method which choices the next node according 
                the Ant System state transition rule

        @param current: vertex from which selecting the next one
        @param vertices: set of all vertices
        @param visited: set of all already visited vertices 
        @return the next node to which jump to
    */
    Vertex state_transition_rule(Vertex current,
                                 const std::set<Vertex>& vertices,
                                 const std::unordered_set<Vertex>& visited) const;

    /*!
        \brief Updating the pheromone intensity according 
            the Ant System pheromone intensity updating rule

        @param cycles: set of all discovered cycles 
    */
    void update_pheromone_intensity(const std::vector<PairPathCost> &cycles);

public:
    /*!
        \brief Ant System class constructor

        @param tsp: tsp to solve
        @param pheromone_intensity: default pheromone intensity
        @param iterations: number of iterations
        @param n_ants: number of ants
        @param alpha: pheromone intensity controller
        @param beta: edge desirability controller
        @param q: just a constant to control the delta update
        @param rho: evaporation factor
        @param name: tsp instance name
    */
    AntSystem(const TSP& tsp,
        double pheromone_intensity,
        double iteration,
        double n_ants,
        double alpha  = 0.9,
        double beta   = 1.5,
        double q      = 10,
        double rho = 0.9,
        const std::string& name = "");

    /*!
        \brief Method that solves tsp via Ant System
    */
    double solve() override;

    /*!
        \brief get the best solution
    */
    std::shared_ptr<Path> get_best_cycle() const override;
  
    /*!
        \brief get the best solution cost
    */
    double get_solution_cost() const override;
};

#endif