#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <set>
#include <iostream>
#include <stdexcept>

template <class V = int, class W = double>
class Graph
{
private:
    typedef std::tuple<V, V, W> Edge;

    int n; int m;

    std::set<Edge *> edges;
    std::map<V, std::map<V, W>> adj_list;

public:
    Graph(std::set<Edge *> edges = {})
    {
        for(auto edge: edges) 
        {
            this->add_edge(std::get<0>(*edge), std::get<1>(*edge), std::get<2>(*edge));
        }
    }

    std::set<V> get_vertices() const
    {
        std::set<V> vertices;

        for(auto& it: adj_list) {
            vertices.insert(it.first);
        }

        return vertices;
    }

    const std::set<Edge *>& get_edges() const
    {
        return this->edges;
    }

    const std::map<V, W>& get_adj_list_by_vertex(const V v) const
    {
        return this->adj_list.at(v);
    }

    W get_weight(const V v, const V t) const
    {
        return this->adj_list.at(v).at(t);
    }

    bool exist_edge(const V v, const V t) const
    {
        try
        {
            this->adj_list.at(v).at(t); return true;
        }
        catch(const std::out_of_range& e)
        {
            return false;
        }
    }

    int get_n() const
    {
        return this->n;
    }

    int get_m() const
    {
        return this->m;
    }

    void add_edge(const V v, const V t, const W w)
    {
        try { this->adj_list.at(v); }
        catch(const std::out_of_range& e) { 
            this->adj_list[v];
            ++n;
        }
        try { this->adj_list.at(t); }
        catch(const std::out_of_range& e) { 
            this->adj_list[t];
            ++n;
        }
        
        std::map<V, W>& adj_list_v = this->adj_list[v];
        adj_list_v[t] = w;

        this->edges.insert(new std::tuple(v, t, w));

        ++m;
    }

    void remove_edge(const V v, const V t)
    {
        this->adj_list.at(v).erase(t);
    }
};

template <class V = int, class W = double>
std::ostream& operator<<(std::ostream& os, const Graph<V, W>& g)
{ 
    os << "(V: " << g.get_n() << ", E: " << g.get_m() << ")" << std::endl;

    std::set<V> vertices = g.get_vertices();

    for(auto& v: vertices)
    {
        const std::map<V, W>& adj_list_v = g.get_adj_list_by_vertex(v);

        os << v << ": {";
        for(auto it = adj_list_v.cbegin(); it != adj_list_v.cend();) {
            os << it->first << ": " << it->second;
            
            ++it;

            if(it != adj_list_v.cend()) os << ", "; 
        }
        os << "}\n";
    }

    return os;
}

#endif
