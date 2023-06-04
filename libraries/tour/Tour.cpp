#include "Tour.h"

Tour::Tour(const std::vector<Vertex>& vertices)
    : vertices(vertices)
{
    if(vertices.empty()) { throw std::runtime_error("Tour is empty"); }

    auto prev = vertices.end() - 1;
    for(auto v = vertices.cbegin(); v != vertices.cend(); ++v)
    {
        edges.emplace_back(*prev, *v);
        prev = v;
    }
}

size_t Tour::index(const Vertex& v) const
{
    auto it = std::find(vertices.cbegin(), vertices.cend(), v);

    return it == vertices.cend() ? -1 : it - vertices.cbegin();
}


//size_t Tour::index(const VertexPair& u_v) const
//{
//    auto it = std::find(edges.cbegin(), edges.cend(), u_v);
//
//    return it == edges.cend() ? -1 : it - edges.cbegin();
//}

//bool Tour::contains(const Vertex& v) const
//{
//    return std::find(vertices.begin(), vertices.end(), v) != vertices.cend();
//}

bool Tour::contains(const VertexPair& v) const
{
    return std::find(edges.begin(), edges.end(), v) != edges.cend();
}

std::vector<Vertex>* Tour::around(const Vertex& v) const
{
    size_t i = index(v);

    std::vector<Vertex> *around = nullptr;

    if(i != -1)
    {
        auto pred = vertices[i == 0 ? vertices.size() - 1 : i - 1];
        auto succ = vertices[i == vertices.size() - 1 ? 0 : i + 1];

        around = new std::vector<Vertex> {pred, succ};
    }

    return around;
}

//std::vector<VertexPair>* Tour::around(const VertexPair& u_v) const
//{
//    size_t i = index(u_v);
//    size_t pred = i - 1;
//    size_t succ = (i + 1) % edges.size();
//
//    if(pred == -1)
//    {
//        pred = edges.size() - 1;
//    }
//
//    return new std::vector<VertexPair>({edges[pred], edges[succ]});
//}

std::vector<Vertex>* Tour::generate(
    const std::vector<VertexPair>& broken,
    const std::vector<VertexPair>& joined
) const
{
    std::vector<VertexPair> new_edges;

    std::set_difference(
            edges.begin(), edges.end(),
            broken.begin(),
            broken.end(),
            std::inserter(new_edges, new_edges.begin()));

    new_edges.insert(new_edges.end(), joined.begin(), joined.end());

    if(new_edges.size() < vertices.size()) return nullptr;

    std::unordered_map<Vertex, Vertex> successors;
    Vertex node = 1;

    while(!new_edges.empty())
    {
        Vertex u;
        Vertex v;

        for(auto u_v : new_edges)
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

        new_edges.erase(std::find(new_edges.cbegin(), new_edges.cend(), VertexPair(u, v)));
    }

    if(successors.size() < vertices.size())
        return nullptr;

    auto *new_tour = new std::vector<Vertex>();

    Vertex starting_node = 1;
    Vertex succ = successors[starting_node];

    new_tour->push_back(starting_node);

    std::vector<Vertex> visited(new_tour->begin(), new_tour->end());

    while(std::find(visited.begin(), visited.end(),succ) == vertices.end())
    {
        visited.push_back(succ);
        new_tour->push_back(succ);
        succ = successors[succ];
    }

    return new_tour;
}
