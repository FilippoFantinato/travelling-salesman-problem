#include "IncompleteTSPFile.h"

IncompleteTSPFile::IncompleteTSPFile(const std::string& section)
    : section(section) { }

const char* IncompleteTSPFile::what() const throw ()
{
    return (section + std::string(" not in the tsp file to read")).c_str();
}
