#include <iostream>
#include <functional>
#include <getopt.h>

#include "./cli/cli.h"

void print_usage()
{
    std::cerr << "usage: tsp --algorithm a [--file f] [--times t]" << std::endl;
    std::cerr << "\t--algorithm a \t: ..." << std::endl;
    std::cerr << "\t--file f \t: ..." << std::endl;
    std::cerr << "\t--times t \t: ..." << std::endl;
}

int read_cli(int argc, char *argv[])
{
    option longopts[] = {
            {"file", required_argument, nullptr, 'f'},
            {"algorithm", required_argument, nullptr, 'a'},
            {"times", optional_argument, nullptr, 't'}
    };

    char *algorithm = nullptr;
    char *file = nullptr;
    long times = 1;

    int opt;
    while((opt = getopt_long(argc, argv, "a:f:t:", longopts, nullptr)) != EOF)
    {
        switch (opt) {
            case 'a':
                algorithm = optarg;
                break;
            case 'f':
                file = optarg;
                break;
            case 't':
                times = strtol(optarg, nullptr, 10);
                break;
            default:
                print_usage();
        }
    }

    if(!algorithm || !file)
    {
        print_usage();
        return 1;
    }

    return CLI::run_file(algorithm, file, times);
}

int main(int argc, char *argv[])
{
    return read_cli(argc, argv);
}
