#ifndef COORDINATE_H
#define COORDINATE_H

#include <iostream>
#include <cmath>

class Coordinate
{
public:
//    virtual ~Coordinate() = 0;
    virtual double distance(const Coordinate&) const = 0;
};

#endif
