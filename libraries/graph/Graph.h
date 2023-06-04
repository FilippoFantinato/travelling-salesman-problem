#ifndef GRAPH_H
#define GRAPH_H

#include <functional>
#include <map>
#include <set>
#include <iostream>
#include <limits>

#include "../utils/hash-combine.h"

template <class V, class W>
class Graph
{
protected:
    typedef std::tuple<V, V, W> Edge;
    typedef std::set<Edge> Edges;

    Edges edges;
    std::set<V> vertices;

public:
    virtual size_t get_n() const = 0;
    virtual size_t get_m() const = 0;

    const std::set<V>& get_vertices() const { return this->vertices; }
    const std::set<Edge>& get_edges() const { return this->edges; }

    virtual const W& get_weight(const V& v, const V& t) const = 0;
    virtual void add_edge(const V& v, const V& t, const W& w) = 0;
    virtual bool exist_edge(const V& v, const V& t) const = 0;

    virtual std::ostream& format(std::ostream& os) const = 0;
};

template<class V, class W>
std::ostream& operator<<(std::ostream& os, const Graph<V, W>& g)
{
    os << g.format(os);
    return os;
}

#endif
