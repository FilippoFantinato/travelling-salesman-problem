#ifndef RADIAN_H
#define RADIAN_H

#include <iostream>
#include <cmath>

class Radian
{
public:
    double rad;

    Radian(double x)
    {
        int integer_part = static_cast<int>(x);
        double decimal_part = x - integer_part;
        this->rad = M_PI * (integer_part + 5.0 * decimal_part / 3.0) / 180.0;
    }

    static double 
};

std::ostream& operator<<(std::ostream& os, const Radian& radian)
{
    os << radian.rad;

    return os;
}

#endif
