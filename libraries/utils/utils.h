#ifndef TSP_UTILS_H
#define TSP_UTILS_H

#include <memory>
#include <cstddef>
#include <iostream>
#include <functional>
#include <algorithm>
#include <chrono>

#define duration(a) std::chrono::duration_cast<std::chrono::milliseconds>(a).count()
#define time_now() std::chrono::high_resolution_clock::now()

/*!
    \brief Some useful util functions
*/
namespace Utils
{
    /*!
        \brief trim from start (in place)
    */
    void ltrim(std::string &s);

    /*!
        \brief trim from end (in place)
    */
    void rtrim(std::string &s);

    /*!
        \brief trim from both ends (in place)
    */
    void trim(std::string &s);

    /*!
        \brief trim from both ends (not in place)
    */
    std::string trim_copy(std::string s);

    /*!
        \brief measure the running time of a given function

        @param f: function to measure the running time
        @return the running time of f in seconds
    */
    double measure_time(const std::function<void(void)>& f);
}

#endif
