#ifndef TOUR_H
#define TOUR_H

#include <vector>
#include <algorithm>
#include <unordered_set>
#include <functional>

#include "VertexPair.h"
#include "../tsp/tsp.h"
#include "../utils/hash-combine.h"

//#include "../graph-functions/compute_cost.h"

//struct VertexPairHasher {
//    size_t operator()(const VertexPair& v) const {
//        auto h1 = std::hash<Vertex>()(v.first);
//        auto h2 = std::hash<Vertex>()(v.second);
//        return Utils::hash_combine(h1, h2);
//    }
//};
//
//typedef std::unordered_set<VertexPair, VertexPairHasher> VertexPairSet;
//typedef std::unordered_set<Vertex> VertexSet;

class Tour
{
private:
    std::vector<VertexPair> edges;
    std::vector<Vertex> vertices;

public:
    Tour(const std::vector<Vertex>& vertices);

    size_t index(const Vertex& v) const;
//    size_t index(const VertexPair& u_v) const;
//    bool contains(const Vertex& v) const;
    bool contains(const VertexPair& v) const;

    std::vector<Vertex>* around(const Vertex& v) const;
//    std::vector<VertexPair>* around(const VertexPair& u_v) const;

    std::vector<Vertex>* generate(const std::vector<VertexPair>&, const std::vector<VertexPair>&) const;

    static double compute_path_cost(const TSP& tsp, const std::vector<Vertex>& path)
    {
        double cost = 0;

        auto prev = path.cbegin();
        for(auto it = std::next(path.cbegin(), 1); it != path.cend(); ++it)
        {
            cost += tsp.get_weight(*prev, *it);
            prev = it;
        }

        return cost;
    }

    static double compute_tour_cost(const TSP& tsp, const std::vector<Vertex>& tour)
    {
        return compute_path_cost(tsp, tour)
               + tsp.get_weight(*tour.rbegin(), *(tour.begin()));
    }
};

#endif
