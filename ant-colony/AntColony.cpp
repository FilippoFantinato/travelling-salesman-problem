#include "AntColony.h"

AntColony::AntColony(
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
}

double AntColony::solve()
{
    for(int i = 0; i < iteration; ++i)
    {
        std::vector<std::shared_ptr<Path>> cycles;

        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> uni(0, tsp.get_vertices().size() - 1);

        std::vector<std::future<std::shared_ptr<Path>>> ants;
        for(int j = 0; j < n_ants; ++j)
        {
            ants.push_back(std::async(std::launch::async, [this, &uni, &rng]{
                Vertex starting_node = uni(rng);
                return this->ant(starting_node);
            }));
        }
        for(const auto& ant: ants) { ant.wait(); }
        for(auto & ant : ants)
        {
            cycles.push_back(ant.get());
        }

        if(best_cycle)
        {
            cycles.push_back(best_cycle);
        }

        update_intensity(cycles);
    }

    return best_cost;
}

// TODO: Optimize it by returning the length of the path
std::shared_ptr<Path> AntColony::ant(Vertex source_node) const
{
    std::unordered_set<Vertex> visited {source_node};
    Vertex current = source_node;
    Path cycle {source_node};
//    double cycle_length = 0;

    for(int steps = 0; steps < (tsp.get_n() - 1); ++steps)
    {
        std::vector<Vertex> jumps_neighbours;
        std::vector<double> jump_probabilities;

//        double sum_probs = 0;
        for(auto& node : tsp.get_vertices())
        {
            if(visited.count(node) == 0)
            {
                double pheromone_level = std::max(intensity[current][node], 1e-5);
                double prob = (pow(pheromone_level, alpha)) * (pow(1/tsp.get_weight(current, node), beta));

//                sum_probs += prob;
                jumps_neighbours.push_back(node);
                jump_probabilities.push_back(prob);
            }
        }

//        for(auto& prob : jump_probabilities)
//        {
//            prob = prob / sum_probs;
//        }

        Vertex next_node = Utils::choice(jumps_neighbours, jump_probabilities);
        visited.insert(next_node);
        cycle.push_back(next_node);

        current = next_node;
    }

    return std::make_shared<Path>(cycle);
}

//void AntColony::update_intensity(const std::vector<std::shared_ptr<Path>>& cycles)
//{
//    for(const auto& cycle: cycles)
//    {
//        double cycle_cost = compute_tour_cost(tsp, *cycle);
//        if(cycle_cost < best_cost)
//        {
//            best_cost  = cycle_cost;
//            best_cycle = cycle;
//        }
//
//        double delta = q / cycle_cost;
//
//        for(int k = 0; k < (cycle->size() - 1); ++k)
//        {
//            auto v = *std::next(cycle->begin(), k);
//            auto u = *std::next(cycle->begin(), k+1);
//
//            intensity[v][u] = intensity[v][u] * evaporation_factor + delta;
//        }
//        intensity[*cycle->rbegin()][*cycle->begin()] =
//                intensity[*cycle->rbegin()][*cycle->begin()] * evaporation_factor + delta;
//    }
//}

void AntColony::update_intensity(const std::vector<std::shared_ptr<Path>>& cycles)
{
    size_t n = tsp.get_n();
    double update_matrix[n][n];

    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            update_matrix[i][j] = 0;
        }
    }

    for(const auto& cycle: cycles)
    {
        double cycle_cost = compute_tour_cost(tsp, *cycle);
        if(cycle_cost < best_cost)
        {
            best_cost  = cycle_cost;
            best_cycle = cycle;
        }

        double delta = q / cycle_cost;

        for(int k = 0; k < (cycle->size() - 1); ++k)
        {
            auto v = *std::next(cycle->begin(), k);
            auto u = *std::next(cycle->begin(), k+1);

            update_matrix[v][u] += delta;
        }
        update_matrix[*cycle->rbegin()][*cycle->begin()] += delta;
    }

    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            intensity[i][j] = (1-evaporation_factor) * intensity[i][j] + update_matrix[i][j];
        }
    }
}


double AntColony::get_solution_cost() const
{
    return best_cost;
}

std::shared_ptr<Path> AntColony::get_best_cycle() const
{
    return best_cycle;
}
