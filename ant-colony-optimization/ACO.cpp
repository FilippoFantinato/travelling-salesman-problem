#include "ACO.h"

ACO::ACO(
        const TSP& tsp,
        double pheromone_level,
        double iteration,
        double n_ants,
        double alpha,
        double beta,
        double q,
        double evaporation_factor,
        const std::string& name)
    : TSPSolver(tsp, name),
    iteration(iteration),
    n_ants(n_ants),
    alpha(alpha),
    beta(beta),
    q(q),
    evaporation_factor(evaporation_factor)
{
    size_t n = tsp.get_n();

    intensity = std::make_unique<std::unique_ptr<double[]>[]>(n);

    for(size_t i = 0; i < n; ++i)
    {
        intensity[i] = std::make_unique<double[]>(n);
        for(size_t j = 0; j < n; ++j)
        {
            intensity[i][j] = pheromone_level;
        }
    }

    this->best_cycle_cost = std::make_pair(nullptr, std::numeric_limits<double>::infinity());
}

double ACO::solve()
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> uni(0, tsp.get_vertices().size() - 1);

    for(int i = 0; i < iteration; ++i)
    {
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

//        for(int j = 0; j < n_ants; ++j)
//        {
//            Vertex starting_node = uni(rng);
//            cycles.push_back(this->ant(starting_node));
//        }

        double best_cost = best_cycle_cost.second;
        for(const auto& current_cycle_cost: cycles)
        {
            auto current_cycle = current_cycle_cost.first;
            double current_cost = current_cycle_cost.second;

            if(current_cost < best_cost)
            {
                best_cycle_cost = current_cycle_cost;
            }
        }

        update_intensity(cycles);
    }

    return best_cycle_cost.second;
}

PairPathCost ACO::ant(Vertex source_node) const
{
    std::unordered_set<Vertex> visited {source_node};
    Vertex current = source_node;
    Path cycle {source_node};
    double cycle_cost = 0;

    for(int steps = 0; steps < (tsp.get_n() - 1); ++steps)
    {
        std::vector<Vertex> jumps_neighbours;
        std::vector<double> jump_probabilities;

        for(auto& node : tsp.get_vertices())
        {
            if(visited.count(node) == 0)
            {
                double pheromone_level = std::max(intensity[current][node], 1e-5);
                double prob = (pow(pheromone_level, alpha)) * (pow(1/tsp.get_weight(current, node), beta));

                jumps_neighbours.push_back(node);
                jump_probabilities.push_back(prob);
            }
        }

        Vertex next_node = Utils::choice(jumps_neighbours, jump_probabilities);
        visited.insert(next_node);
        cycle.push_back(next_node);
        cycle_cost += tsp.get_weight(current, next_node);

        current = next_node;
    }

    cycle_cost += tsp.get_weight(*cycle.rbegin(), *cycle.begin());

    return std::make_pair(std::make_shared<Path>(cycle), cycle_cost);
}

void ACO::update_intensity(const std::vector<PairPathCost>& cycles)
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

        double delta = q / current_cost;

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
            intensity[i][j] = (1-evaporation_factor) * intensity[i][j] + delta_matrix[i][j];
        }
    }
}


double ACO::get_solution_cost() const
{
    return best_cycle_cost.second;
}

std::shared_ptr<Path> ACO::get_best_cycle() const
{
    return best_cycle_cost.first;
}
