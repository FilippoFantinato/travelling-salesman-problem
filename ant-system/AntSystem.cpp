#include "AntSystem.h"

AntSystem::AntSystem(
        const TSP& tsp,
        double pheromone_intensity,
        double iterations,
        double n_ants,
        double alpha,
        double beta,
        double q,
        double rho,
        const std::string& name)
    : TSPSolver(tsp, name),
    iterations(iterations),
    n_ants(n_ants),
    alpha(alpha),
    beta(beta),
    Q(q),
    rho(rho)
{
    size_t n = tsp.get_n();

    intensity = std::make_unique<std::unique_ptr<double[]>[]>(n);
    for(size_t i = 0; i < n; ++i)
    {
        intensity[i] = std::make_unique<double[]>(n);
        for(size_t j = 0; j < n; ++j)
        {
            intensity[i][j] = pheromone_intensity;
        }
    }

    this->best_cycle_cost = std::make_pair(nullptr, std::numeric_limits<double>::infinity());
}

double AntSystem::solve()
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> uni(0, tsp.get_vertices().size() - 1);

    for(int i = 0; i < iterations; ++i)
    {
        // Run the ants concurrently and store all the cycles
        std::vector<PairPathCost> cycles;
        std::vector<std::future<PairPathCost>> ants;
        for(int j = 0; j < n_ants; ++j)
        {
            ants.push_back(std::async(std::launch::async, [this, &uni, &rng]{
                Vertex starting_node = uni(rng);
                return this->ant(starting_node);
            }));
        }
        for(const auto& ant: ants) { ant.wait(); }
        for(auto& ant : ants)
        {
            cycles.push_back(ant.get());
        }

        // Find the best cycle
        for(const auto& current_cycle_cost: cycles)
        {
            if(current_cycle_cost.second < best_cycle_cost.second)
            {
                best_cycle_cost = current_cycle_cost;
            }
        }

        // Update the pheromone intensity
        update_pheromone_intensity(cycles);
    }

    return best_cycle_cost.second;
}

PairPathCost AntSystem::ant(Vertex source_node) const
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

        current = next_node;
    }

    cycle_cost += tsp.get_weight(*cycle.rbegin(), *cycle.begin());

    return std::make_pair(std::make_shared<Path>(cycle), cycle_cost);
}

Vertex AntSystem::state_transition_rule(Vertex current,
                           const std::set<Vertex>& vertices,
                           const std::unordered_set<Vertex>& visited) const
{
    std::vector<Vertex> jumps_neighbours;
    std::vector<double> jump_probabilities;

    for(auto& node : vertices) if(visited.count(node) == 0) {
        double pheromone_intensity = intensity[current][node];
        double prob = (pow(pheromone_intensity, alpha)) * (pow(1/tsp.get_weight(current, node), beta));

        jumps_neighbours.push_back(node);
        jump_probabilities.push_back(prob);
    }

    return Math::choice(jumps_neighbours, jump_probabilities);
}

void AntSystem::update_pheromone_intensity(const std::vector<PairPathCost>& cycles)
{
    size_t n = tsp.get_n();
    double delta_matrix[n][n];

    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            delta_matrix[i][j] = 0;
        }
    }

    for(const auto& current_cycle_cost: cycles)
    {
        auto current_cycle = current_cycle_cost.first;
        double current_cost = current_cycle_cost.second;

        double delta = Q / current_cost;

        for(int k = 0; k < (current_cycle->size() - 1); ++k)
        {
            auto v = *std::next(current_cycle->begin(), k);
            auto u = *std::next(current_cycle->begin(), k+1);

            delta_matrix[v][u] += delta;
        }
        delta_matrix[*current_cycle->rbegin()][*current_cycle->begin()] += delta;
    }

    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            intensity[i][j] = (1-rho) * intensity[i][j] + delta_matrix[i][j];
        }
    }
}

double AntSystem::get_solution_cost() const
{
    return best_cycle_cost.second;
}

std::shared_ptr<Path> AntSystem::get_best_cycle() const
{
    return best_cycle_cost.first;
}
