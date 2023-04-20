#include "EdgeWeightNotHandled.h"

EdgeWeightNotHandled::EdgeWeightNotHandled(std::string edge_weight)
    : edge_weight(edge_weight) { }


const char* EdgeWeightNotHandled::what() const throw ()
{
    return (edge_weight + std::string(" not handled")).c_str();
}
