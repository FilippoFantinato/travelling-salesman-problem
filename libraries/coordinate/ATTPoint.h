#ifndef ATT_POINT_H
#define ATT_POINT_H

#include <cmath>

#include "Coordinate.h"

class ATTPoint : public Coordinate
{
public:
    const double x;
    const double y;

    ATTPoint(double x, double y);

    double distance(const Coordinate& att_point) const override;
};

#endif
