#ifndef CLI_H
#define CLI_H

#include "./initializers.h"
#include "../libraries/tsp-file/tsp-file.h"
#include "../libraries/utils/measure-time.h"

namespace CLI
{
    int run_file(const char *algorithm, const char *f, long times);
    int run_directory(const char *algorithm, const char *d, long times);

    std::unique_ptr<TSPSolver> get_solver(const char *algorithm, const TSP& tsp);
}

#endif
