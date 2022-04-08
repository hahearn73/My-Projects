/**
 ** main.cpp
 **
 ** lab11
 **
 ** Purpose:
 **   A place to driver to help practicing BFS and DFS for lab11 2021
 **
 **
 ** ChangeLog:
 **   17 Nov 2020: zgolds01
 **       main.cpp driver created
 **   12 April 2021: mchamp03
 **       Refactored for use in lab10
 **
 **/

#include <fstream>
#include <ios>
#include <iostream>
#include <string>

#include "PathFinder.h"

void usage(std::string progname) {
    std::cerr << "Usage: " << progname << " cityFile" << std::endl;
}

void assert_file(std::ios& file, std::string filename) {
    if (not file.good()) {
        std::cerr << filename << " cannot be opened." << std::endl;
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char* argv[]) {

    PathFinder    pf;
    std::ifstream data;

    switch (argc) {

    case 2: /* 1st positional arg is city file */
        data.open(argv[1]);
        assert_file(data, argv[1]);
        pf.populate_graph(data);
        data.close();

        break;

    default:
        usage(argv[0]);
        exit(EXIT_FAILURE);
        break;
    }

    pf.run();

    /* It is not necessary to close these file streams because there
     * is no need to free up resources immediately before program
     * termination (streams are closed automatically when they pass
     * out of scope).
     */
    data.close();

    return 0;
}
