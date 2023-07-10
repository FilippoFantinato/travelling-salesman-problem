#ifndef TSP_COORDINATE_H
#define TSP_COORDINATE_H

#include <iostream>
#include <cmath>

class Coordinate
{
public:
//    virtual ~Coordinate() = 0;
    virtual double distance(const Coordinate&) const = 0;
};

#endif
