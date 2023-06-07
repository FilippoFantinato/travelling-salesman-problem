#include "NearestNeighbour.h"


NearestNeighbour::NearestNeighbour(const TSP& tsp, Vertex starting_node, const std::string& name)
    : TSPSolver(tsp, name), starting_node(starting_node) { }

double NearestNeighbour::solve()
{
    Vertex current = starting_node;
    std::unordered_set<Vertex> visited {current};

    best_cycle = std::make_shared<Path>();
    best_cost = 0;

    best_cycle->push_back(current);
    for(int i = 0; i < (tsp.get_n()-1); ++i)
    {
        Vertex closer_vertex = current;
        double closer_weight = std::numeric_limits<double>::infinity();
        for(int u = 0; u < tsp.get_n(); ++u)
        {
            if(tsp.exist_edge(current, u) && visited.count(u) == 0)
            {
                double w = tsp.get_weight(current, u);
                if(w < closer_weight)
                {
                    closer_vertex = u;
                    closer_weight = w;
                }
            }
        }

        visited.insert(closer_vertex);
        best_cycle->push_back(closer_vertex);
        best_cost += closer_weight;

        current = closer_vertex;
    }
    best_cost += tsp.get_weight(current, starting_node);

    return best_cost;
}

std::shared_ptr<Path> NearestNeighbour::get_best_cycle() const { return best_cycle; }

double NearestNeighbour::get_solution_cost() const { return best_cost; }
