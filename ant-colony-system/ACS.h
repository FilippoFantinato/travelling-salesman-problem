#ifndef ACS_H
#define ACS_H

#include <cmath>
#include <iterator>
#include <future>
#include <thread>

#include "../libraries/path/path.h"
#include "../libraries/tsp-solvers/TSPSolver.h"
#include "../libraries/utils/random.h"

typedef std::pair<std::shared_ptr<Path>, double> PairPathCost;

class ACS : public TSPSolver
{
private:
    const double iteration;
    const double n_ants;
    const double beta;
    const double q0;
    const double rho;
    const double evaporation_factor;
    const double default_pheromone_level;

    std::unique_ptr<std::unique_ptr<double[]>[]> intensity;

    PairPathCost best_cycle_cost;

    PairPathCost ant(Vertex source_node);

    Vertex state_transition_rule(Vertex current,
                                 const std::set<Vertex>& vertices,
                                 const std::unordered_set<Vertex>& visited) const;
    void global_updating_rule();
    void local_updating_rule(Vertex r, Vertex s);

public:
    ACS(const TSP& tsp,
        double pheromone_level,
        double iteration,
        double n_ants,
        double beta = 2,
        double q0   = 0.9,
        double rho  = 0.1,
        double evaporation_factor = 0.1,
        const std::string& name = "");

    double solve() override;
    double get_solution_cost() const override;
    std::shared_ptr<Path> get_best_cycle() const override;
};

#endif