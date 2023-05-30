#include "Tour.h"

Tour::Tour(const std::vector<Vertex>& tour) : tour(tour), cost(0), gain(0)
{
    if(tour.empty()) { throw std::runtime_error("Tour is empty"); }
    
    auto prev = (tour.cend() - 1);
    for(auto v = tour.cbegin(); v != tour.cend(); ++v)
    {
        push_back(VertexPair(*prev, *v));
        prev = v;
    }
}

int Tour::index(const Vertex& v) const
{
    auto it = std::find(tour.cbegin(), tour.cend(), v);

    return it != tour.cend() ? it - tour.cbegin() : -1;
}


int Tour::index(const VertexPair& u_v) const
{
    auto it = std::find(cbegin(), cend(), u_v);

    return it != cend() ? it - cbegin() : -1;
}

std::vector<Vertex> Tour::around(const Vertex& v) const
{
    int i = index(v);
    int pred = i - 1;
    int succ = (i + 1) % tour.size();

    if(pred == -1)
    {
        pred = tour.size() - 1;
    }

    return {tour[pred], tour[succ]};
}

std::vector<VertexPair> Tour::around(const VertexPair& u_v) const
{
    int i = index(u_v);
    int pred = i - 1;
    int succ = (i + 1) % size();

    if(pred == -1)
    {
        pred = size() - 1;
    }

    return {operator[](pred), operator[](succ)};
}

std::vector<Vertex>* Tour::generate(
    const std::vector<VertexPair>& broken, 
    const std::vector<VertexPair>& joined
) const
{
    std::vector<VertexPair> edges;
//    TODO: check if the error is due to that edges is empty

    std::set_difference(begin(), end() - 1, broken.begin(), broken.end() - 1, edges.begin());
    edges.insert(edges.end(), joined.begin(), joined.end());

    if(edges.size() < size()) return nullptr;

    std::unordered_map<Vertex, Vertex> successors;
    Vertex node = 1;

    while(!edges.empty())
    {
        Vertex u;
        Vertex v;

        for(auto& u_v : edges)
        {
            u = u_v.first;
            v = u_v.second;

            if(u == node)
            {
                successors[node] = v;
                node = v;
                break;
            }
            else if(v == node)
            {
                successors[node] = u;
                node = u;
                break;
            }
        }

        edges.erase(std::find(edges.cbegin(), edges.cend(), VertexPair(u, v)));
    }

    std::vector<Vertex> *new_tour = nullptr;

    if(successors.size() >= size())
    {
        Vertex succ = successors[1];
        new_tour = new std::vector<Vertex>({succ});

        std::unordered_map<Vertex, bool> visited({{succ, true}});

        while(visited.count(succ) == 0)
        {
            visited[succ] = true;
            new_tour->push_back(succ);
            succ = successors[succ];
        }
    }

    return new_tour;
}
