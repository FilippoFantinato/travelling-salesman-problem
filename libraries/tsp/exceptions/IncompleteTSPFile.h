#ifndef INCOMPLETE_TSP_FILE_H
#define INCOMPLETE_TSP_FILE_H

#include <exception>
#include <string>

class IncompleteTSPFile : public std::exception
{
private:
    const std::string section;

public:
    IncompleteTSPFile(std::string section);
    
    const char* what() const throw ();
};

#endif