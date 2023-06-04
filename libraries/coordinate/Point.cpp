#include "Point.h"

Point::Point(double x, double y) : x(x), y(y) { } 

double Point::distance(const Coordinate& point) const
{
    const auto& p = dynamic_cast<const Point&>(point);

    return round(sqrt(pow(this->y - p.y, 2) + pow(this->x - p.x, 2)));
} 
