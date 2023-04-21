#include "ATTPoint.h"

ATTPoint::ATTPoint(double x, double y) : x(x), y(y) {}

double ATTPoint::distance(const Coordinate& att_point) const
{
    const ATTPoint& att = dynamic_cast<const ATTPoint&>(att_point);
    
    double xd = x - att.x;
    double yd = y - att.y;
    double r = sqrt((pow(xd, 2) + pow(yd, 2)) / 10.0);
    double t = round(r);
    double d = t < r ? t + 1 : t;
    
    return d;
}
