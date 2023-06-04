#include "AntColony.h"

AntColony::AntColony(
        const TSP& tsp,
        double pheromone_level,
        double iteration,
        double n_ants,
        const std::string& name,
        double q,
        double degradation_factor)
    : TSPSolver(tsp, name),
    iteration(iteration),
    n_ants(n_ants),
    q(q),
    degradation_factor(degradation_factor)
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
        std::vector<VertexVector_ptr> cycles;

        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> uni(0, tsp.get_vertices().size() - 1);

        std::vector<std::future<VertexVector_ptr>> ants;
        for(int j = 0; j < n_ants; ++j)
        {
            ants.push_back(std::async(std::launch::async, [this, &uni, &rng]{
                Vertex starting_node = uni(rng);
                return this->traverse_graph(starting_node);
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

        for(const auto& cycle: cycles)
        {
            double cycle_cost = Tour::compute_tour_cost(tsp, *cycle);
            if(cycle_cost < best_cost)
            {
                best_cost  = cycle_cost;
                best_cycle = cycle;
            }

            double delta = q / cycle_cost;
            double factor = 1 - degradation_factor;

            for(int k = 0; k < (cycle->size() - 1); ++k)
            {
                auto v = *std::next(cycle->begin(), k);
                auto u = *std::next(cycle->begin(), k+1);

                intensity[v][u] *= factor;
            }
            intensity[*cycle->rbegin()][*cycle->begin()] *= factor;
        }
    }

    return best_cost;
}

std::shared_ptr<std::vector<Vertex>> AntColony::traverse_graph(Vertex source_node) const
{
    double ALPHA = 0.9;
    double BETA  = 1.5;

    std::unordered_set<Vertex> visited {source_node};

    Vertex current = source_node;
    std::vector<Vertex> cycle {source_node};

    for(int steps = 0; steps < (tsp.get_n() - 1); ++steps)
    {
        std::vector<Vertex> jumps_neighbours;
        std::vector<double> jump_values;

        for(auto& node : tsp.get_vertices())
        {
            if(visited.count(node) == 0)
            {
                double pheromone_level = std::max(intensity[current][node], 1e-5);
                double v = (pow(pheromone_level, ALPHA)) / (pow(tsp.get_weight(current, node), BETA));

                jumps_neighbours.push_back(node);
                jump_values.push_back(v);
            }
        }
        Vertex next_node = Utils::choice(jumps_neighbours, jump_values);

        visited.insert(next_node);
        current = next_node;
        cycle.push_back(current);
    }

    return std::make_shared<std::vector<Vertex>>(cycle);
}

double AntColony::get_solution_cost() const
{
    return best_cost;
}
