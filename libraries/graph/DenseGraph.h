#ifndef DENSE_GRAPH_H
#define DENSE_GRAPH_H

#include <memory>
#include "Graph.h"

template <class V, class W>
class DenseGraph : public Graph<V, W>
{
protected:
    size_t n;

    std::unique_ptr<std::unique_ptr<W[]>[]> matrix;

public:
    DenseGraph(size_t dim) : Graph<V, W>(), n(dim) {
        matrix = std::make_unique<std::unique_ptr<W[]>[]>(n);
        for(size_t i = 0; i < n; ++i)
        {
            matrix[i] = std::make_unique<W[]>(n);
            for(size_t j = 0; j < n; ++j)
            {
                matrix[i][j] = std::numeric_limits<W>::infinity();
            }
        }
    }

    size_t get_n() const override { return this->n; }
    size_t get_m() const override { return this->edges.size(); }

    const std::map<V, W>& get_adj_list_by_vertex(const V& v) const
    {
        return this->adj_list.at(v);
    }

    const W& get_weight(const V& v, const V& t) const override
    {
        return this->matrix[v][t];
    }

    bool exist_edge(const V& v, const V& t) const override
    {
        return matrix[v][t] != std::numeric_limits<W>::infinity();
    }

    void add_edge(const V& v, const V& t, const W& w) override
    {
        Graph<V, W>::vertices.insert(v);
        Graph<V, W>::vertices.insert(t);

        this->matrix[v][t] = w;

        this->edges.insert(std::tuple(v, t, w));
    }

    std::ostream& format(std::ostream& os) const override {
        os << "(V: " << n <<
           ", E: " << get_m() << ")" << std::endl;

        for(size_t i = 0; i < n; ++i)
        {
            os << i << ": {";
            for(size_t j = 0; j < n; ++j)
            {
                os << j << ": " << matrix[i][j];

                if((j+1) != n) os << ", ";
            }
            os << "}";
        }

        return os;
    }
};

#endif