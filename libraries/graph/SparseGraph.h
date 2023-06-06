#ifndef SPARSE_GRAPH_H
#define SPARSE_GRAPH_H

#include <vector>

#include "Graph.h"

template <class V, class W>
class SparseGraph : public Graph<V, W>
{
protected:
    std::map<V, std::map<V, W>> adj_list;

public:
    size_t get_n() const { return this->vertices.size(); }
    size_t get_m() const { return this->edges.size(); }

    const std::map<V, W>& get_adj_list_by_vertex(const V& v) const
    {
        return this->adj_list.at(v);
    }

    const W& get_weight(const V& v, const V& t) const override
    {
        return exist_edge(v, t) ? this->adj_list.at(v).at(t)
                : std::numeric_limits<W>::infinity();
    }

    bool exist_edge(const V& v, const V& t) const override
    {
        return adj_list.count(v) && adj_list.at(v).count(t);
    }

    void add_edge(const V& v, const V& t, const W& w) override
    {
        Graph<V, W>::vertices.insert(v);
        Graph<V, W>::vertices.insert(t);

        this->adj_list[v][t] = w;

        this->edges.insert(std::make_tuple(v, t, w));
    }

    std::ostream& format(std::ostream& os) const override {
        os << "(V: " << Graph<V, W>::get_n() <<
              ", E: " << Graph<V, W>::get_m() << ")" << std::endl;

        for(const auto& v: adj_list)
        {
            const auto& adj = adj_list.at(v);
            os << v << ": {";
            for(const auto& it = adj.cbegin(); it != adj.end(); ++it ) {
                os << it->first << ": " << it->second;

                if(it != adj.cend()) os << ", ";
            }
            os << "}";
        }

        return os;
    }
};

#endif
