

#include "PathFinder.h"
#include <vector>
#include <queue>
#include <random>

enum code{PRINT, BFS, DFS, STOP, ERROR};

code hash_str(std::string s){
    if (s == "print") return PRINT;
    if (s == "p")     return PRINT;
    if (s == "Print") return PRINT;
    if (s == "bfs")   return BFS;
    if (s == "dfs")   return DFS;
    if (s == "stop")  return STOP;
    if (s == "quit")  return STOP;
    if (s == "q")     return STOP;
    if (s == "Quit")  return STOP;
    if (s == "exit")  return STOP;
    if (s == "Exit")  return STOP;
    return ERROR;
}



PathFinder::PathFinder()
{
    // Nothing to do for Graph class, it self initializes
    // Initialize random seed
    srand(time(NULL));
}



PathFinder::~PathFinder()
{
    // Nothing to do, graph and PathFinder class self destruct
}

bool PathFinder::run_bfs(std::string c1, std::string c2)
{
    bool ret = false;
    std::queue<City> q;
    q.push(graph.get_vertex(c1));
    graph.mark_vertex(graph.get_vertex(c1)); // mark it as visited
    while (not q.empty()) {
        City c = q.front();
        q.pop();

        std::vector<std::string> neighbors = c.get_neighbors();
        for (int i = 0; i < c.get_num_neighbors(); i++) {
            if (not graph.is_marked(graph.get_vertex(neighbors[i]))) { // not marked
                graph.mark_vertex(graph.get_vertex(neighbors[i])); // mark it
                q.push(graph.get_vertex(neighbors[i])); // queue it
                graph.update_predecessor(c, graph.get_vertex(neighbors[i]));
            }
            if (neighbors[i] == c2)
                ret = true;
        }
    }
    return ret;
}

bool PathFinder::run_dfs(City c1, City c2)
{
    if (c1 == c2)
        return true;
    std::vector<std::string> neighbors = c1.get_neighbors();
    for (int i = 0; i < c1.get_num_neighbors(); i++) {
        if (not graph.is_marked(graph.get_vertex(neighbors[i]))) {
            if (run_dfs(graph.get_vertex(neighbors[i]), c2)) {
                graph.update_predecessor(c1, graph.get_vertex(neighbors[i]));
                return true;
            }
        }
    }
    return false;
}


// IGNORE THE FUNCTIONS BELOW.... Don't look behind the curtain! haha


std::pair<std::string, std::string> PathFinder::get_cities()
{
    std::string city1, city2;
    std::cout << "City 1? ";
    std::cin >> city1;
    std::cout << "City 2? ";
    std::cin >> city2;
    return std::make_pair(city1, city2);
}



void PathFinder::bfs()
{
    std::pair<std::string, std::string> cities = get_cities();
    if (run_bfs(cities.first, cities.second)) {
        graph.report_path(std::cout, cities.first, cities.second);
    } else {
        std::cout << "No flight from " << cities.first << " to "
                  << cities.second
                  << ".\n";
    }
    graph.clear_marks();
}




void PathFinder::dfs()
{

    std::pair<std::string, std::string> cities = get_cities();
    City city1 = graph.get_vertex(cities.first);
    City city2 = graph.get_vertex(cities.second);

    if (run_dfs(city1, city2)) {
        graph.report_path(std::cout, city1, city2);
    } else {
        std::cout << "No flight from " << city1.get_name() << " to "
                  << city2.get_name() << ".\n";
    }
    graph.clear_marks();
}





void PathFinder::run()
{
    std::string cmnd = "";
    std::cout << "Command? ";
    try
    {
       while(std::cin >> cmnd) {
            switch (hash_str(cmnd))
            {
            case 0:
                graph.print_matrix(std::cout);
                break;
            case 1:
                bfs();
                break;
            case 2:
                dfs();
                break;
            case 3:
                clean_up();
                return;
            default:
                std::cout << "Command not recognized! Try again." << std::endl;
                break;
            }

            std::cout << "Command? ";
        }
        clean_up();
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << '\n';
        run();
    }


}

void PathFinder::clean_up()
{
    std::cout << "Thanks for finding paths and such" << std::endl;
}

std::string get_airline()
{
    std::string airlines[] = {"Delta", "American Airlines", "Spirit", "Virgin",
                              "Jet Blue", "Southwest", "United"};
    int random = rand() % 7;
    return airlines[random];
}

void PathFinder::populate_graph(std::ifstream &data)
{
    std::string vertex = "";
    std::vector<City> cities;
    while(data >> vertex) {
        City c(vertex);
        while(data >> vertex) {
            if (vertex == "###") {
                cities.push_back(c);
                break;
            } else {
                c.add_neighbor(vertex);
            }
        }
    }

    graph.initialize_graph(cities.size());

    for (auto &city : cities) {
        graph.add_vertex(city);
    }
    for (auto &city : cities) {
        for(auto &edge: city.get_neighbors()) {
            graph.add_edge(city, edge, get_airline());
        }
    }

}
