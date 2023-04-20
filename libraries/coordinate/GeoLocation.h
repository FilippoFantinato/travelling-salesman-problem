#ifndef GEOLOCATION_H
#define GEOLOCATION_H

#include "Coordinate.h"

class GeoLocation : public Coordinate
{
private:
    static double to_radian(double d);

public:
    const double longitude; 
    const double latitude;

    GeoLocation(double x, double y);

    double distance(const Coordinate& geo_location) const override;
};

#endif