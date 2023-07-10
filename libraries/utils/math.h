#ifndef TSP_UTILS_MATH_H
#define TSP_UTILS_MATH_H

#include <iostream>
#include <vector>
#include <cmath>
#include <random>


/*!
    \brief Some useful mathematical functions
*/
namespace Math
{
    /*!
        \brief round n to the decimal digit after the comma

        @param n: the number to round
        @param decimal: the position of the decimal to which round n
        @return the rounded number
    */
    double round(double n, int decimal);

    /*!
        \brief compute the relative error

        @param approx: value of the approximate solution
        @param optimal: value of the optimal solution
        @return the relative error of approx w.r.t. optimal
    */
    double relative_error(double approx, double actual);

    /*!
        \brief compute the standard deviation
    */
    template<class T>
    double std_dev(const std::vector<T>& xs, double mean)
    {
        double s = 0;
        for(const auto& x: xs)
        {
            s += pow(x - mean, 2);
        }

        return sqrt(s / xs.size());
    }

    /*!
        \brief random weighted choice

        @param choices: the set of elemnts from which selecting
        @param weights: the corresponding weight for each element in choices
        @return an element of choices chosen according to its weight randomly
    */
    template<class V>
    V choice(const std::vector<V> choices, const std::vector<double>& weights)
    {
        std::random_device rd;
        std::discrete_distribution<> dist(weights.begin(), weights.end());
        std::mt19937 gen(rd());

        return choices[dist(gen)];
    }
}

#endif
