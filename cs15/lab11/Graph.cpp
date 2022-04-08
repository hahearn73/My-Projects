
/*
 * Graph.cpp
 * Project 2: Six Degrees of Collaboration
 * Graph class updated by rgilk01 and jdavid07 11/13/20
 */

#include <iostream>
#include <string>
#include <stack>
#include "Graph.h"
using namespace std;

// Default constructor
Graph::Graph()
{
    curr_vertex = 0;
    edges       = nullptr;
    path        = nullptr;
    vertices    = nullptr;
    marks       = nullptr;
}

Graph::Graph(int num_v)
{
    initialize_graph(num_v);
}

void Graph::initialize_graph(int num_v)
{
    curr_vertex = 0;
    num_vertices = num_v;
    vertices = new City[num_vertices];
    marks = new bool[num_vertices];
    path = new int[num_vertices];

    edges = new string*[num_vertices];
    for (int i = 0; i < num_vertices; i++)
        edges[i] = new string[num_vertices];

    for (int i = 0; i < num_vertices; i++) {
        marks[i] = false;
        path[i] = NULL_PRED;
        for (int j = 0; j < num_vertices; j++)
            edges[i][j] = NULL_EDGE;
    }
}

// Destructor (two dynamic arrays)
Graph::~Graph()
{
    delete [] vertices;
    delete [] marks;
    delete [] path;
    for (int i = 0; i < num_vertices; i++)
        delete [] edges[i];

    delete [] edges;
}

// Copy constructor
Graph::Graph(const Graph &other)
{
    num_vertices = other.num_vertices;

    vertices = new City[num_vertices];
    marks = new bool[num_vertices];
    path = new int[num_vertices];

    edges = new string *[num_vertices];
    for (int i = 0; i < num_vertices;  i++)
        edges[i] = new string[num_vertices];

    for (int i = 0; i < num_vertices; i++) {
        vertices[i] = other.vertices[i];
        marks[i] = other.marks[i];
        path[i] = other.path[i];
        for (int j = 0; j < num_vertices; j++)
            edges[i][j] = other.edges[i][j];
    }

}

// Assignment Operator
Graph &Graph::operator=(const Graph &rhs)
{
    delete [] marks;
    delete [] vertices;
    delete [] path;
    for (int i = 0; i < num_vertices; i++)
        delete [] edges[i];

    delete [] edges;


    num_vertices = rhs.num_vertices;

    vertices = new City[num_vertices];
    marks    = new bool[num_vertices];

    path     = new int[num_vertices];
    edges    = new string *[num_vertices];
    for (int i = 0; i < num_vertices;  i++)
        edges[i] = new string[num_vertices];

    for (int i = 0; i < num_vertices; i++) {
        vertices[i] = rhs.vertices[i];
        marks[i] = rhs.marks[i];
        path[i] = rhs.path[i];
        for (int j = 0; j < num_vertices; j++)
            edges[i][j] = rhs.edges[i][j];
    }

    return *this;
}

// Function add_vertex
// Parameters: Vertex, by value
// Returns: void
// Does: Add a new vertex to the end of the 2d array
//       Initializes every from/to edge to be NULL
void Graph::add_vertex(City v)
{
    if (curr_vertex >= num_vertices)
        return;

     vertices[curr_vertex] = v;
     for (int i = 0; i < num_vertices; i++) {
         edges[curr_vertex][i] = NULL_EDGE;
         edges[i][curr_vertex] = NULL_EDGE;
     }
     curr_vertex++;
 }

// Function clear_marks
// Parameters: none
// Returns: none
// Does: For algorithms that need to mark vertices (BFS, DFS)
//       sets all the marks to be false
void Graph::clear_marks()
{
    for (int i = 0; i < num_vertices; i++) {
        marks[i] = false;
        path[i] = NULL_PRED;
    }
}

// Function initialize_path
// Parameters: none
// Returns: none
// Does: Sets every value in the predecessor path to be the NULL edge
void Graph::initialize_path()
{
    for (int i = 0; i < num_vertices; i++)
        path[i] = NULL_PRED;
}

// Function update_predecessor
// Parameters: Two vertices, the predecessor and the current
// Returns: None
// Does: Finds the location in the vertices array for predecessor
//       and current. Updates the path array to reflect pred relationship.
void Graph::update_predecessor(City pred, City curr)
{
    int pred_index, curr_index;
    for (int i = 0; i < num_vertices; i++) {
        if (vertices[i] == pred) {
            pred_index = i;
        }
        if (vertices[i] == curr) {
            curr_index = i;
        }
    }
    if (path[curr_index] == NULL_PRED)
        path[curr_index] = pred_index;
}

// Function report_path
// Parameters: Ostream to print, start and end vertices
// Returns: nonde
// Does: Finds path from start to end on the predecessor path and prints
void Graph::report_path(ostream &out, City start, City end) const
{
    if (start == end) {
        out << "You don't need to fly from " << start.get_name() << " to " 
            << end.get_name() << "!\n";
        return;
    }
    stack<City> s;

    int index = index_is(vertices, end.get_name());
    s.push(vertices[index]);

    bool done = false;
    while (not done) {
        index = path[index];
               
        if (vertices[index].get_name() == start.get_name())
            done = true;
        s.push(vertices[index]);
    }

    while (!s.empty())
    {
        City v = s.top();
        s.pop();
        if (!s.empty())
        {
            City v2 = s.top();
            out << v.get_name() << " ---> ";
            out << v2.get_name() << " through ";
            out << get_edge(v, v2) << ".  ";
        }

    }
    out << "\nend of flight!" << endl;
}

// Function mark_vertex
// Parameters: Vertex
// Returns: none
// Does: Sets the mark of this vertex to true
void Graph::mark_vertex(City v)
{
    for (int i = 0; i < num_vertices; i++) {
        if (vertices[i] == v)
            marks[i] = true;
    }
}

// Function is_marked
// Parameters: Vertex
// Returns: bool
// Does: returns value in marks array for this vertex
bool Graph::is_marked(City v) const
{
    for (int i = 0; i < num_vertices; i++) {
        if (vertices[i] == v)
            return marks[i];
    }
    return false;
}

// Function is_vertex
// Parameters: Vertex
// Returns: bool
// Does: returns true if vertex exists in the graph,
//       false otherwise.
bool Graph::is_vertex(City v) const
{
    for (int i = 0; i < num_vertices; i++) {
        if (vertices[i] == v)
            return true;
    }
    return false;
}

// Function add_edge
// Parameters: Two vertices (from and to), weight of the edge
// Returns: void
// Does: updates edges array to have the given weight
void Graph::add_edge(City f, City t, string weight)
{
     int row;
     int col;

     row = index_is(vertices, f);
     col = index_is(vertices, t);
     if (edges[row][col] == NULL_EDGE)
         edges[row][col] = weight;
}

// Function get_vertex
// Parameters: int, a position
// Returns: vertex at that given position
City Graph::get_vertex(std::string s) const
{
        
    for(int i = 0; i < num_vertices; i++) {
        if (s == vertices[i].get_name()) {
            return vertices[i];
        }
    }
    throw runtime_error("No city " + s + " in Graph. Try again.");
    // return vertices[0];
}

// Function get_edge
// Parameters: Two vertices (from and to)
// Returns: string, the name of the edge (sort of a weight)
string Graph::get_edge(City from, City to) const
{
     int row;
     int col;
     row = index_is(vertices, from);
     col = index_is(vertices, to);
     return edges[row][col];
}

// Function get_to_vertices
// Parameters: Vertex, queue of vertices by reference
// Returns: void
// Does: Finds all neighbors of the given vertex and enqueues
void Graph::get_to_vertices(City v, queue<City> &adj) const
{
    int from;
    int to;
    from = index_is(vertices, v);
    for (to = 0; to < num_vertices; to++) {
        if (edges[from][to] != NULL_EDGE) {
            if (vertices[to] != vertices[from]) {
                   adj.push(vertices[to]);
            }
        }
    }
}

// Function print_matrix
// Parameters: ostream
// Returns: void
void Graph::print_matrix(ostream &out) const
{
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++)
            out << edges[i][j] << " ";
        out << endl;
    }
}

// wrapper function definitions
int index_is(City *vertices, City v)
{
    int index = 0;
    while (not (v.get_name() == vertices[index].get_name()))
        index++;
    return index;
}
