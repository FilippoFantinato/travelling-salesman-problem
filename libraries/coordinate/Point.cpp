#include "Point.h"

Point::Point(double x, double y) : x(x), y(y) { } 

double Point::distance(const Coordinate& point) const
{
    const Point& p = dynamic_cast<const Point&>(point);

    return sqrt(pow(this->y - p.y, 2) + pow(this->x - p.x, 2));
} 