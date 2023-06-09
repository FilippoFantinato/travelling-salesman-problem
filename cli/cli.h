#ifndef CLI_H
#define CLI_H

#include <vector>

#include "../libraries/tsp-file/tsp-file.h"
#include "../libraries/utils/measure-time.h"

#include "./initializers.h"
#include "Solution.h"

namespace CLI
{
    typedef std::vector<Solution> Solutions;
    typedef std::pair<std::shared_ptr<const TSPFile::TSPInformation>, std::shared_ptr<const Solutions>> InfoSolutions;

    InfoSolutions run_file(const char *algorithm, const char *f, long times);
    InfoSolutions run_directory(const char *algorithm, const char *d, long times);

    std::unique_ptr<TSPSolver> get_solver(const char *algorithm, const TSP& tsp);
}

#endif
