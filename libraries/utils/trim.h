#ifndef UTILS_TRIM_H
#define UTILS_TRIM_H

#include <string>
#include <algorithm> 

namespace Utils
{
    // trim from start (in place)
    void ltrim(std::string &s);

    // trim from end (in place)
    void rtrim(std::string &s);

    // trim from both ends (in place)
    void trim(std::string &s);

    std::string trim_copy(std::string s);
}

#endif
