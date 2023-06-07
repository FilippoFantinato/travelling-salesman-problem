#ifndef DENSE_GRAPH_H
#define DENSE_GRAPH_H

#include <memory>
#include <vector>

#include "Graph.h"

template <class V, class W>
class DenseGraph : public Graph<V, W>
{
protected:
    const size_t n;

    std::vector<std::vector<W>> matrix;

public:
    DenseGraph(size_t dim) : Graph<V, W>(), n(dim) {
        matrix = std::vector<std::vector<W>>(n);
        for(size_t i = 0; i < n; ++i)
        {
            matrix[i] = std::vector<W>(n);
            for(size_t j = 0; j < n; ++j)
            {
                matrix[i][j] = std::numeric_limits<W>::infinity();
            }
        }
    }

    int get_n() const override { return this->n; }
    int get_m() const override { return this->edges.size(); }

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

        this->edges.insert(std::make_tuple(v, t, w));
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