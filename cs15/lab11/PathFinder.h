

#ifndef _PATH_FINDER_H_
#define _PATH_FINDER_H_

#include "Graph.h"
#include <iostream>
#include <fstream>

class PathFinder
{

    public:
        PathFinder();
        ~PathFinder();

        void run();
        void populate_graph(std::ifstream &data);
        void bfs();
        void dfs();


    private:

        Graph graph;

        void clean_up();

        bool run_bfs(std::string city1, std::string city2);
        bool run_dfs(City city1, City city2);
        std::pair<std::string, std::string> get_cities();

};


#endif