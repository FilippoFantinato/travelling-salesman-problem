#ifndef GRAPH_FUNCTIONS_H
#define GRAPH_FUNCTIONS_H

#include <vector>

#include "../graph/SparseGraph.h"
#include "../tour/Tour.h"

//template <class V, class W>
//int compute_path_cost(const Graph<V, W>& g, const VertexSet& path)
//{
//    int cost = 0;
//
//    auto prev = path.cbegin();
//    for(auto it = path.cbegin() + 1; it != path.cend(); ++it, prev = it)
//    {
//        cost += g.get_weight(*prev, *it);
//    }
//
//    return cost;
//}

//template <class V, class W>
//int compute_tour_cost(const Graph<V, W>& g, const VertexSet& tour)
//{
//    return compute_path_cost(g, tour)
//            + g.get_weight(*(tour.cend() - 1), *(tour.cbegin()));
//}


#endif