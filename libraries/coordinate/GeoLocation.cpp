#include "GeoLocation.h"

double GeoLocation::to_radian(double d)
{
    double PI = 3.141592;
    // double deg = static_cast<int>(d);
    // double min = d - deg;
    // double rad = M_PI * (deg + 5.0*min/3.0) / 180.0;
    // return rad;
    return PI * d / 180.0;
}

GeoLocation::GeoLocation(double x, double y)
    : longitude(to_radian(x)), latitude(to_radian(y)) {}

double GeoLocation::distance(const Coordinate& geo_location) const
{
    const GeoLocation& geo = dynamic_cast<const GeoLocation&>(geo_location);
    
    double RRR = 6378.388;
    double q1 = cos(longitude - geo.longitude);
    double q2 = cos(latitude - geo.latitude);
    double q3 = cos(latitude + geo.latitude);
    double d = round(RRR * acos(0.5 * ((1.0 + q1) * q2 - (1.0 - q1) * q3)) + 1.0);

    return d;
}
