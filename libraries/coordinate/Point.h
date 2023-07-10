#ifndef TSP_POINT_H
#define TSP_POINT_H

#include "Coordinate.h"

class Point : public Coordinate
{
public:   
    const double x; 
    const double y;
    
    Point(double x, double y);

    double distance(const Coordinate& point) const override;
};

#endif
