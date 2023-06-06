#include "ACS.h"

ACS::ACS(
        const TSP& tsp,
        double pheromone_level,
        double iteration,
        double n_ants,
        double beta,
        double q0,
        double rho,
        double evaporation_factor,
        const std::string& name)
    : TSPSolver(tsp, name),
      iteration(iteration),
      n_ants(n_ants),
      beta(beta),
      q0(q0),
      rho(rho),
      evaporation_factor(evaporation_factor),
      default_pheromone_level(pheromone_level)
{
    size_t n = tsp.get_n();

    intensity = std::make_unique<std::unique_ptr<double[]>[]>(n);

    for(size_t i = 0; i < n; ++i)
    {
        intensity[i] = std::make_unique<double[]>(n);
        for(size_t j = 0; j < n; ++j)
        {
            intensity[i][j] = default_pheromone_level;
        }
    }

    this->best_cycle_cost = std::make_pair(nullptr, std::numeric_limits<double>::infinity());
}

double ACS::solve()
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> uni(0, tsp.get_vertices().size() - 1);

    for(int i = 0; i < iteration; ++i)
    {
        std::vector<PairPathCost> cycles;

        for(int j = 0; j < n_ants; ++j)
        {
            Vertex starting_node = uni(rng);
            cycles.push_back(this->ant(starting_node));
        }

        for(const auto& current_cycle_cost: cycles)
        {
            auto current_cycle = current_cycle_cost.first;
            double current_cost = current_cycle_cost.second;

            if (current_cost < best_cycle_cost.second) {
                best_cycle_cost = current_cycle_cost;
            }
        }

        global_updating_rule();
    }

    return best_cycle_cost.second;
}

PairPathCost ACS::ant(Vertex source_node)
{
    auto vertices = tsp.get_vertices();
    std::unordered_set<Vertex> visited {source_node};
    Vertex current = source_node;
    Path cycle {source_node};
    double cycle_cost = 0;

    for(int steps = 0; steps < (tsp.get_n() - 1); ++steps)
    {
        Vertex next_node = state_transition_rule(current, vertices, visited);


        visited.insert(next_node);
        cycle.push_back(next_node);
        cycle_cost += tsp.get_weight(current, next_node);

        local_updating_rule(current, next_node);

        current = next_node;
    }

    cycle_cost += tsp.get_weight(*cycle.rbegin(), *cycle.begin());

    return std::make_pair(std::make_shared<Path>(cycle), cycle_cost);
}

Vertex ACS::state_transition_rule(
        Vertex current,
        const std::set<Vertex>& vertices,
        const std::unordered_set<Vertex>& visited) const
{
    Vertex next_node;

    double q = ((double)rand()) / RAND_MAX;

    if(q <= q0)
    {
        Vertex max_node = current; double max_value = -std::numeric_limits<double>::infinity();
        for(auto& node : vertices) if (visited.count(node) == 0) {
            double pheromone_level = std::max(intensity[current][node], 1e-5);
            double current_value = pheromone_level * (pow(1/tsp.get_weight(current, node), beta));

            if(current_value > max_value)
            {
                max_value = current_value;
                max_node = node;
            }
        }
        next_node = max_node;
    }
    else
    {
        std::vector<Vertex> jumps_neighbours;
        std::vector<double> jump_probabilities;

        for(auto& node : vertices) if(visited.count(node) == 0) {
            double pheromone_level = intensity[current][node];
            double prob = pheromone_level * (pow(1/tsp.get_weight(current, node), beta));

            jumps_neighbours.push_back(node);
            jump_probabilities.push_back(prob);
        }

        next_node = Utils::choice(jumps_neighbours, jump_probabilities);
    }
    return next_node;
}

void ACS::global_updating_rule()
{
    int n = tsp.get_n();

    auto best_cycle = best_cycle_cost.first;
    double best_cost = best_cycle_cost.second;
    double delta = evaporation_factor * (1/best_cost);

    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            intensity[i][j] = (1-evaporation_factor) * intensity[i][j];

            auto it = find(best_cycle->begin(), best_cycle->end(), i);
            if(it != best_cycle->end())
            {
                auto next_it = (it == (best_cycle->end()-1)) ? best_cycle->begin() : it + 1;
                if(*next_it == j) intensity[i][j] += delta;
            }
        }
    }
}

void ACS::local_updating_rule(Vertex r, Vertex s)
{
    double delta = rho * default_pheromone_level;

    intensity[r][s] = (1-rho) * intensity[r][s] + delta;
}


double ACS::get_solution_cost() const
{
    return best_cycle_cost.second;
}

std::shared_ptr<Path> ACS::get_best_cycle() const
{
    return best_cycle_cost.first;
}
