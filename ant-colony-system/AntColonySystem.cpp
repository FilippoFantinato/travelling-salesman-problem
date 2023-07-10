#include "AntColonySystem.h"

AntColonySystem::AntColonySystem(
        const TSP& tsp,
        double pheromone_intensity,
        double iterations,
        double n_ants,
        double alpha,
        double beta,
        double q0,
        double rho,
        const std::string& name)
    : TSPSolver(tsp, name),
      iterations(iterations),
      n_ants(n_ants),
      alpha(alpha),
      beta(beta),
      q0(q0),
      rho(rho),
      default_pheromone_intensity(pheromone_intensity)
{
    size_t n = tsp.get_n();

    intensity = std::make_unique<std::unique_ptr<double[]>[]>(n);

    for(size_t i = 0; i < n; ++i)
    {
        intensity[i] = std::make_unique<double[]>(n);
        for(size_t j = 0; j < n; ++j)
        {
            intensity[i][j] = default_pheromone_intensity;
        }
    }

    this->best_cycle_cost = std::make_pair(nullptr, std::numeric_limits<double>::infinity());
}

double AntColonySystem::solve()
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> uni(0, tsp.get_vertices().size() - 1);

    for(int i = 0; i < iterations; ++i)
    {
        // Run the ants and store all the cycles
        std::vector<PairPathCost> cycles;
        for(int j = 0; j < n_ants; ++j)
        {
            Vertex starting_node = uni(rng);
            cycles.push_back(this->ant(starting_node));
        }

        // Find the best cycle
        for(const auto& current_cycle_cost: cycles)
        {
            if (current_cycle_cost.second < best_cycle_cost.second) {
                best_cycle_cost = current_cycle_cost;
            }
        }

        // Update the pheromone intensity globally
        global_updating_rule();
    }

    return best_cycle_cost.second;
}

PairPathCost AntColonySystem::ant(Vertex source_node)
{
    size_t n = tsp.get_n();
    const auto& vertices = tsp.get_vertices();
    std::unordered_set<Vertex> visited {source_node};
    Vertex current = source_node;
    Path cycle {source_node};
    double cycle_cost = 0;

    for(int steps = 0; steps < (n - 1); ++steps)
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

Vertex AntColonySystem::state_transition_rule(Vertex current,
                           const std::set<Vertex>& vertices,
                           const std::unordered_set<Vertex>& visited) const
{
    Vertex next_node;

    double q = ((double)rand()) / RAND_MAX;

    if(q <= q0)
    {
        Vertex max_node = current; double max_value = -std::numeric_limits<double>::infinity();
        for(auto& node : vertices) if (visited.count(node) == 0) {
            double pheromone_intensity = intensity[current][node];
            double current_value = pheromone_intensity * (pow(1/tsp.get_weight(current, node), beta));

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
            double pheromone_intensity = intensity[current][node];
            double prob = pheromone_intensity * (pow(1/tsp.get_weight(current, node), beta));

            jumps_neighbours.push_back(node);
            jump_probabilities.push_back(prob);
        }

        next_node = Math::choice(jumps_neighbours, jump_probabilities);
    }
    return next_node;
}

void AntColonySystem::local_updating_rule(Vertex r, Vertex s)
{
    double delta = rho * default_pheromone_intensity;

    intensity[r][s] = (1-rho) * intensity[r][s] + delta;
}

void AntColonySystem::global_updating_rule()
{
    int n = tsp.get_n();

    auto best_cycle = best_cycle_cost.first;
    double best_cost = best_cycle_cost.second;
    double delta = alpha * (1/best_cost);

    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            intensity[i][j] = (1-alpha) * intensity[i][j];

            auto it = find(best_cycle->begin(), best_cycle->end(), i);
            if(it != best_cycle->end())
            {
                auto next_it = (it == (best_cycle->end()-1)) ? best_cycle->begin() : it + 1;
                if(*next_it == j) intensity[i][j] += delta;
            }
        }
    }
}

double AntColonySystem::get_solution_cost() const
{
    return best_cycle_cost.second;
}

std::shared_ptr<Path> AntColonySystem::get_best_cycle() const
{
    return best_cycle_cost.first;
}
