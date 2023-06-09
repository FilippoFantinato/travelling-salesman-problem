#ifndef TSP_EDGE_WEIGHT_NOT_HANDLED_H
#define TSP_EDGE_WEIGHT_NOT_HANDLED_H

#include <exception>
#include <string>

class EdgeWeightNotHandled : public std::exception
{
private:
    const std::string edge_weight;

public:

    EdgeWeightNotHandled(const std::string& edge_weight);

    const char* what() const throw ();
};

#endif