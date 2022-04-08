/*
Harry Ahearn SixDegrees CollabGraph_test.cpp cs15 12/05/21
This file tests the 3 functions students must implement in the CollabGraph 
class. It does this using a main function which calls 3 functions that run
various tests. Output must then be checked for accuracy of the different 
functions tested. 
*/

#include <iostream>
#include "Artist.h"
#include "CollabGraph.h"
#include <vector>
using namespace std;

/* populate_graph_test
 * creates 2 CollabGraph objects and tests that their populate_graph function 
 * works as expected
 * returns nothing
 */
void populate_graph_test()
{
    vector<Artist> artists, artists2; // making the artists
    Artist a("a");
    a.add_song("song1");
    a.add_song("song2");
    Artist b("b");
    b.add_song("song1");
    Artist c("c");
    artists.push_back(a);
    artists.push_back(b);
    artists.push_back(c);
    
    CollabGraph graph, graph2;
    graph.populate_graph(artists);
    graph.enforce_valid_vertex(c); // make sure c exists in graph
    graph.print_graph(cout); // nothing for c should be printed
    c.add_song("song2"); // modify c
    c.add_song("song3");
    b.add_song("song3");
    artists2.push_back(a);
    artists2.push_back(b);
    artists2.push_back(c);
    graph2.populate_graph(artists2);
    graph2.print_graph(cout); // c should now be printed wiht one song with a/b
}

/* print_stack
 * prints a stack of artists to cout
 * returns nothing, parameters are stack to be printed
 */
void print_stack(stack<Artist>& s)
{
    while (not s.empty()) {
        Artist temp = s.top();
        s.pop();
        cout << temp.get_name() << " ";
    }
    cout << endl;
}

/* report_path_test
 * tests the report_path function by printing its output to cout so it can be 
 * checked for accuracy
 * NOTE: only works when there is no private data in CollabGraph (comment out 
 * the word private for this to work and uncomment the funciton)
 */
void report_path_test()
{
    vector<Artist> artists;
    Artist a("a");
    a.add_song("song1");
    Artist b("b");
    b.add_song("song1");
    b.add_song("song2");
    Artist c("c");
    c.add_song("song2");
    Artist d("d");
    
    artists.push_back(a);
    artists.push_back(b);
    artists.push_back(c);
    artists.push_back(d);
    
    CollabGraph cb;
    cb.populate_graph(artists);
    // cb.graph["a"]->predecessor = nullptr;
    // cb.graph["b"]->predecessor = cb.graph["a"];
    // cb.graph["c"]->predecessor = cb.graph["b"];
    // cb.graph["d"]->predecessor = nullptr;
    // stack<Artist> b_to_a = cb.report_path(a, b);
    // stack<Artist> c_to_a = cb.report_path(a, c);
    // stack<Artist> c_to_b = cb.report_path(b, c);
    // stack<Artist> d_to_a = cb.report_path(a, d);
    // 
    // print_stack(b_to_a);
    // print_stack(c_to_a);
    // print_stack(c_to_b);
    // print_stack(d_to_a); // should be an empty line
}

/* print_vector
 * prints names of a vector of artists
 * parameters: v is a vector of artists to be printed
 */
void print_vector(vector<Artist> v)
{
    for (size_t i = 0; i < v.size(); i++)
        cout << v[i].get_name() << " ";
    cout << endl;
}

/* get_vertex_neighbors_test
 * tests the get_vertex_neighbors function
 */
void get_vertex_neighbors_test()
{
    vector<Artist> artists;
    Artist a("a");
    a.add_song("song1");
    Artist b("b");
    b.add_song("song1");
    b.add_song("song2");
    Artist c("c");
    c.add_song("song2");
    Artist d("d");
    
    artists.push_back(a);
    artists.push_back(b);
    artists.push_back(c);
    artists.push_back(d);
    
    CollabGraph cb;
    cb.populate_graph(artists);
    vector<Artist> a_neighbors = cb.get_vertex_neighbors(a);
    vector<Artist> b_neighbors = cb.get_vertex_neighbors(b);
    vector<Artist> c_neighbors = cb.get_vertex_neighbors(c);
    vector<Artist> d_neighbors = cb.get_vertex_neighbors(d);
    print_vector(a_neighbors);
    print_vector(b_neighbors);
    print_vector(c_neighbors);
    print_vector(d_neighbors); // should be an empty line
}

int main()
{
    populate_graph_test();
    report_path_test();
    get_vertex_neighbors_test();
    return 0;
}