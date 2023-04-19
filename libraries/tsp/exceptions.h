#ifndef TSP_EXCEPTIONS_H
#define TSP_EXCEPTIONS_H

#include <exception>
#include <string>

class EdgeWeightTypeNotHandled : std::exception
{
private:
    const std::string edge_weight_type;

public:

    EdgeWeightTypeNotHandled(std::string edge_weight_type)
    : edge_weight_type(edge_weight_type) { }

    const char* what() const throw ()
    {
        return (edge_weight_type + std::string(" not handled")).c_str();
    }
};


class IncompleteTSPFile : std::exception
{
private:
    const std::string section;

public:
    IncompleteTSPFile(std::string section) : section(section) { }
    
    const char* what() const throw ()
    {
        return (section + std::string(" not in the tsp file to read")).c_str();
    }
};

#endif