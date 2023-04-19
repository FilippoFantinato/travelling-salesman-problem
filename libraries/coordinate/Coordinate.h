#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <cmath>

class Coordinate
{
public:
    virtual double distance(const Coordinate&) const = 0;
};

class Point : public Coordinate
{
public:   
    const double x; 
    const double y;
    
    Point(double x, double y) : x(x), y(y) { } 

    double distance(const Coordinate& point) const override
    {
        const Point& p = dynamic_cast<const Point&>(point);

        return round(sqrt(pow(this->y - p.y, 2) + pow(this->x - p.x, 2)));
    } 
};

class GeoLocation : public Coordinate
{
private:
    static double to_radian(double d)
    {
        double deg = static_cast<int>(d);
        double min = d - deg;
        double rad = M_PI * (deg + 5.0*min/3.0) / 180.0;
        return rad;
    }

public:
    const double longitude; 
    const double latitude;

    GeoLocation(double x, double y): 
        longitude(to_radian(x)), latitude(to_radian(y)) {}

    double distance(const Coordinate& geo_location) const override
    {
        const GeoLocation& geo = dynamic_cast<const GeoLocation&>(geo_location);
        
        const double RRR = 6378.388;
        double q1 = cos(longitude - geo.longitude);
        double q2 = cos(latitude - geo.latitude);
        double q3 = cos(latitude + geo.latitude);
        double d = (int) (RRR * acos(0.5 * ((1.0 + q1) * q2 - (1.0 - q1) * q3)) + 1.0);

        return d;
    }
};

#endif
