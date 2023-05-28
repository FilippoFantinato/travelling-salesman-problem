#include "lin_kernighan.h"

LinKernighan::LinKernighan(const TSP& tsp)
    : TSPSolver(tsp) {}


double LinKernighan::solve() 
{
    bool better = true;

    for(auto v : path)
    {
        if(neighbours.count(v) == 0) neighbours[v] = {};

        for(auto e : tsp.get_adj_list_by_vertex(v))
        {
            Vertex u = e.first;
            Weight w = e.second; 
            if(w > 0 && (std::find(path.cbegin(), path.cend(), u) != path.cend()))
            {
                neighbours[v].push_back(u);
            }
        }
    }

    while(better)
    {
        better = improve();
        solutions[path] = true;
    }

    return 42;
}

bool LinKernighan::improve()
{
    Tour tour(path);

    for(auto u : path)
    {
        std::vector<Vertex> around = tour.around(u);
        for(auto v : around)
        {
            double gain = tsp.get_weight(u, v);
            std::vector<VertexPair> broken({VertexPair(u, v)});

            auto close = closest(v, tour, gain, broken, {});

            int tries = 5;

            for(auto& el : close)
            {
                const Vertex& t = el.first;
                const double& g = el.second[1];

                if(std::find(around.cbegin(), around.cend(), t) == around.cend())
                {
                    std::vector<VertexPair> joined({VertexPair(v, t)});

                    if(chooseX(tour, u, t, g, broken, joined))
                    {
                        return true;
                    }

                    tries -= 1;

                    if(tries == 0) break;
                }
            }
        }
    }

    return false;
}

std::unordered_map<Vertex, std::vector<Vertex>> LinKernighan::closest(
		const Vertex& v, 
		const Tour& tour, 
		int gain, 
		const std::vector<VertexPair>& broken, 
		const std::vector<VertexPair>& joined)
{
    std::unordered_map<Vertex, std::vector<double>> neighbours;

    for(auto u : this->neighbours[v])
    {
        VertexPair v_u(v, u);
        double g = gain - tsp.get_weight(v, u);

        if((g <= 0) || 
           (std::find(broken.cbegin(), broken.cend(), u) == broken.cend()) || 
           (tour.index(v_u) != -1))
        {
            continue;
        }

        for(auto t : tour.around(u))
        {
            VertexPair u_t(u, t);

            if((std::find(broken.cbegin(), broken.cend(), u_t) == broken.cend()) && 
               (std::find(joined.cbegin(), joined.cend(), u_t) == joined.cend()))
            {
                double diff = tsp.get_weight(u, t) - tsp.get_weight(v, u);

                if(neighbours.count(u) && diff > neighbours[u][0])
                {
                    neighbours[u][0] = diff;
                }
                else
                {
                    neighbours[u] = {diff, g};
                }
            }
        }
    }

    // return std::sort(neighbours.)
    return {};
}


bool LinKernighan::chooseX(
		const Tour& tour,
		const Vertex& v,
		const Vertex& last,
		double gain,
		const std::vector<VertexPair>& broken,
		const std::vector<VertexPair>& joined)
{
    std::vector<Vertex> around;
    if(broken.size() == 4) {
        std::vector<Vertex> tmp = tour.around(last);
        const Vertex& pred = tmp[0];
        const Vertex& succ = tmp[1];
        
        around.push_back(tsp.get_weight(pred, last) > tsp.get_weight(succ, last) 
                            ? pred : succ);
    } else {
        around = tour.around(last);
    }

    for(auto& u : around)
    {
        VertexPair last_u(last, u);

        double g = gain + tsp.get_weight(last, u);

        if(std::find(joined.begin(), joined.cend(), last_u) == joined.cend() &&
        std::find(broken.cbegin(), broken.cend(), last_u) == broken.cend())
        {
            std::vector<VertexPair> added(joined);
            std::vector<VertexPair> removed(broken);

            removed.push_back(last_u);
            added.push_back(VertexPair(u, v));

            double relink = g - tsp.get_weight(u, v);
            std::vector<Vertex> *new_tour = tour.generate(removed, added);

            if(new_tour != NULL || added.size() <= 2)
            {
                if(new_tour != NULL && relink > 0)
                {
                    // TODO: FIX IT
                    path = new_tour;
                    cost -= relink;
                    return true;
                }
                else
                {
                    bool choice = chooseY(tour, v, u, g, removed, joined);

                    if(broken.size() == 2 && choice)
                    {
                        return true;
                    }
                    else
                    {
                        return choice;
                    }
                }
            }
        }
    }

    return false;
}

bool LinKernighan::chooseY(
    const Tour& tour,
    const Vertex& v,
    const Vertex& u,
    double gain,
    const std::vector<VertexPair>& broken,
    const std::vector<VertexPair>& joined)
{
    auto ordered = closest(u, tour, gain, broken, joined);
    
    int top = broken.size() == 2 ? 5 : 3;

    for(auto& el: ordered)
    {
        const Vertex& t = el.first;
        VertexPair u_t(u, t);

        std::vector<VertexPair> added(joined);
        added.push_back(u_t);

        if(chooseX(tour, v, t, gain, broken, added))
        {
            return true;
        }

        top -= 1;

        if(top == 0)
        {
            return true;
        }
    }

    return false;
}
