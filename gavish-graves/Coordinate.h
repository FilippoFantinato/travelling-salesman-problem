#ifndef POINT_H
#define POINT_H

#include <cmath>

class Coordinate
{
public:
    virtual double distance(const Coordinate&) const = 0;
};

class Point : public Coordinate
{
public:   
    const double x; const double y;
    Point(double x, double y) : x(x), y(y) { } 

    double distance(const Point& p) override const
    {
        return round(sqrt(pow(p1.y - p2.y, 2) + pow(p1.x - p2.x, 2)));
    } 
};

class GEOLocation : public Coordinate
{
private:
    static double to_radian(double x)
    {
        int integer_part = static_cast<int>(d);
        double decimal_part = d - integer_part;
        double rad = M_PI * (integer_part + 5.0 * decimal_part / 3.0) / 180.0;
        return rad;
    }

public:
    const double longitude; const double latitude;

    GEOLocation(double x, double y): 
        longitude(to_radian(x)), latitude(to_radian(y)) {}

    double distance(const GEOLocation& geo) override const
    {
        const double RRR = 6378.388;

        double q1 = cos(longitude - geo.longitude);
        double q2 = cos(latitude - geo.latitude);
        double q3 = cos(latitude + geo.latitude);
        double d = static_cast<int>(RRR * acos(0.5 * ((1.0 + q1) * q2 - (1.0 - q1) * q3)) + 1.0);

        return d;
    }
}

std::ostream& operator<<(std::ostream& os, const Point& p)
{ 
    os << "(" << p.x << ", " << p.y << ")";

    return os;
}

std::ostream& operator<<(std::ostream& os, const GEOLocation& geo)
{ 
    os << "(" << geo.longitude << ", " << geo.latitude << ")";

    return os;
}

#endif
