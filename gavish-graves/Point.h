#ifndef POINT_H
#define POINT_H

struct Point
{
    const double x; const double y;

    Point(double x, double y) : x(x), y(y) { } 
};

std::ostream& operator<<(std::ostream& os, const Point& p)
{ 
    os << "(" << p.x << ", " << p.y << ")";

    return os;
}

#endif
