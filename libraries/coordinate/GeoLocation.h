#ifndef TSP_GEOLOCATION_H
#define TSP_GEOLOCATION_H

#include "Coordinate.h"

class GeoLocation : public Coordinate
{
private:
    static double to_radian(double d);

public:
    const double latitude;
    const double longitude; 

    GeoLocation(double x, double y);

    double distance(const Coordinate& geo_location) const override;
};

#endif
