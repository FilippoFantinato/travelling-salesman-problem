#ifndef TSP_GRAPH_H
#define TSP_GRAPH_H

#include <iostream>
#include <memory>
#include <limits>
#include <vector>
#include <set>

/*!
    \brief Class representing a dense undirected graph via adjicent matrix

    @param V: vertices type
    @param W: weights type
*/

template <class V, class W>
class Graph
{
protected:
    typedef std::tuple<V, V, W> Edge;

    const size_t n;
    std::set<Edge> edges;
    std::set<V> vertices;
    std::vector<std::vector<W>> matrix;

public:
    /*!
        \brief Graph class constructor.
               It initializes only the adjianct matrix lower diagonal,
               given that it represents a undirected graph

        @param dim: number of nodes
    */
    Graph(size_t dim) : n(dim) {
        matrix = std::vector<std::vector<W>>(n);
        for(size_t i = 0; i < n; ++i)
        {
            size_t k = i+1;
            matrix[i] = std::vector<W>(k);
            for(size_t j = 0; j < k; ++j)
            {
                matrix[i][j] = std::numeric_limits<W>::infinity();
            }

            vertices.insert(i);
        }
    }

    /*! \brief get the number of nodes */
    int get_n() const { return this->n; }

    /*! \brief get the number of edges */
    int get_m() const { return this->edges.size(); }

    /*! \brief get the set of all vertices */
    const std::set<V>& get_vertices() const { return this->vertices; }

    /*! \brief get the set of all edges */
    const std::set<Edge>& get_edges() const { return this->edges; }

    /*!
        \brief get the weight related to an edge

        @param v, t: represents the edge (v,t)
    */
    const W& get_weight(const V& v, const V& t) const
    {
        V v1 = v; V v2 = t;
        if(v < t) { v1 = t; v2 = v; }

        return this->matrix[v1][v2];
    }

    /*!
        \brief checks whether an edge exists

        @param v, t: represents the edge (v,t)
    */
    bool exist_edge(const V& v, const V& t) const
    {
        return matrix[v][t] != std::numeric_limits<W>::infinity();
    }

    /*!
        \brief add an edge to the adjiacent matrix and the set of edges.
               If the edge already exists, then before remove it from the set of edges

        @param v, t: represents the edge (v,t)
        @param w: weight of the edge (v,t)
    */
    void add_edge(const V& v, const V& t, const W& w)
    {
        V v1 = v; V v2 = t;
        if(v < t) { v1 = t; v2 = v; }

        if(this->exist_edge(v1, v2))
        {
            this->edges.erase(std::make_tuple(v1, v2, this->get_weight(v1, v2)));
        }

        this->matrix[v1][v2] = w;
        this->edges.insert(std::make_tuple(v, t, w));
    }
};

template<class V, class W>
std::ostream& operator<<(std::ostream& os, const Graph<V, W>& g)
{
    int n = g.get_n();
    int m = g.get_m();

    os << "(V: " << n <<
       ", E: " << m << ")" << std::endl;

    for(size_t i = 0; i < n; ++i)
    {
        os << i << ": {";
        for(size_t j = 0; j < n; ++j)
        {
            os << j << ": " << g.get_weight(i, j);

            if((j+1) != n) os << ", ";
        }
        os << "}";
    }

    return os;
}

#endif