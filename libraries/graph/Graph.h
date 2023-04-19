#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <set>
#include <iostream>

template <class V, class W>
class Graph {
private:
    typedef std::tuple<V, V, W> Edge;

    std::set<Edge *> edges;
    std::set<V> vertices;
    std::map<V, std::map<V, W>> adj_list;

public:
    // Graph(const std::set<Edge *> edges& = std::set())
    // {
    //     for(auto edge: edges) 
    //     {
    //         this->add_edge(std::get<0>(*edge), std::get<1>(*edge), std::get<2>(*edge));
    //     }
    // }

    const std::set<V>& get_vertices() const
    {
        return this->vertices;
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
            this->adj_list.at(v).at(t); 
            return true;
        }
        catch(const std::out_of_range& e)
        {
            return false;
        }
    }

    int get_n() const { return this->vertices.size(); }
    int get_m() const { return this->edges.size(); }

    void add_edge(const V v, const V t, const W w)
    {
        vertices.insert(v); vertices.insert(t);

        this->adj_list[v][t] = w;
        this->edges.insert(new std::tuple(v, t, w));
    }

    bool remove_edge(const V v, const V t)
    {
        try
        {
            this->adj_list.at(v).erase(t);
            
            if(this->adj_list.at(v).size() == 0)
            {
                this->adj_list.erase(v);
                vertices.erase(vertices.find(v));
            }
            return true;
        }
        catch(const std::exception& e)
        {
            return false;
        }
    }
};

template <class V, class W>
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
        os << "}";
    }

    return os;
}

#endif