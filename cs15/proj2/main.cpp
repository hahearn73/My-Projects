/*
 * main.cpp - checks that files provided to SixDegrees program is correct and 
 * works. Creates a SixDegrees object and gives the artist istream to the 
 * constructor so the CollabGraph can be created. Then calls run on the object
 * and passes it input or output files cin and cout depending on the command
 * line arguments.
 * COMP 15 Project 2: Six Degrees of Collaboration
 * 
 * by Harry Ahearn 12/6/21
 */
#include <iostream>
#include <istream>
#include <fstream>
#include "Artist2.h"
#include "CollabGraph.h"
#include "SixDegrees.h"
using namespace std;

template<typename streamtype>
void open_or_die(streamtype &stream, string file_name);
void abort(string error_message);

/* main 
 * checks command line parameters as files for errors. creates a SixDegrees 
 * object and calls its run function.
 * parameters: the amount of command line arguments and the arguments
 * returns 0 if successful
 */
int main(int argc, char *argv[])
{
    if (not (argc == 2 or argc == 3 or argc == 4))
        abort("Usage: SixDegrees dataFile [commandFile] [outputFile]");
    ifstream commands;
    ofstream output;
    ifstream artists;
    open_or_die(artists, argv[1]);
    SixDegrees s(artists); // create object
    if (argc == 2) 
        s.run(cin, cout);
    else if (argc == 3) {
        open_or_die(artists, argv[1]);
        open_or_die(commands, argv[2]);
        s.run(commands, cout); // no output file
        commands.close();
    }
    else {
        open_or_die(artists, argv[1]);
        open_or_die(commands, argv[2]);
        open_or_die(output, argv[3]);
        s.run(commands, output); // all files
        commands.close();
        output.close();
    }
    artists.close(); // closes artist no matter what
    return 0;
}

/*
 * abort 
 * ends program and prints reason why
 * parameter: error_message is the reason to be printed
 */
void abort(string error_message)
{
        cerr << error_message << endl;
        exit(EXIT_FAILURE);
}

/*
 * Try to open the given file.
 * Abort on failure.
 * If the function returns, caller can assume stream is open.
 */
template<typename streamtype>
void open_or_die(streamtype &stream, string file_name)
{
        stream.open(file_name);
        if (not stream.is_open())
            abort(file_name + " cannot be opened.");
}
