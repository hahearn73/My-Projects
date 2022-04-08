//                            fileread.cpp
//                         Author: Noah Mendelsohn
//
//         Demonstration of reading lines from a named file
//

#include <iostream>
#include <fstream>    // *** Needed to use ifstream ***

using namespace std;

struct classInfo {
    string dept;
    int class_number;
};

classInfo readLine(ifstream& input_file);
void printClassInfo(classInfo class1);

int
main(int argc, char* argv[])
{
        string filename = argv[1];
        // TODO: declare variable for department and class number
        
        //
        // Create a variable of type ifstream
        // "if" stands for "input file"
        // used for reading input files
        // ofstream is for output files
        //
        ifstream input_file;

        //
        // Before you can use an input file stream, you must
        // "open" it, which connects the C++ stream with the
        // file on the disk.  In this case, schedule1.data
        // in the current directory.
        //
        input_file.open(filename);

        //
        // Make sure that we could successfully open the file
        // (maybe we got the filename wrong?).  If
        // not, just write an error message and return from main.
        //
        if (not input_file.is_open()) {
                cerr << "fileread.cpp: could not open file: "
                     << filename << endl;
                return 1;           // non-zero return from main means error
        }
        
        classInfo class1, class2;
        class1 = readLine(input_file);
        class2 = readLine(input_file);
        
        // printing file data
        printClassInfo(class1);
        printClassInfo(class2);
        
        // printing out the filename
        if(argc == 2) {
            cout << "Found in: " << argv[1] << endl;
        }

        // When you are done with a file, you "close" it, 
        // which tells C++ do any cleaning up that is necessary
        input_file.close();

        return 0;
}

/*
 * Purpose:   reads a line from a file and stores it as a classInfo struct
 * Args:      the file being read from
 * Returns:   returns the new struct that has been constructed
 * Notes:     requires fstream
 */
classInfo readLine(ifstream& input_file) {
    classInfo class1;
    input_file >> class1.dept;
    input_file >> class1.class_number;
    return class1;
}

/*
 * Purpose:   prints out the dept and number of a classInfo struct 
 * Args:      the struct 
 * Returns:   void 
 *
 */
void printClassInfo(classInfo class1) {
    cout << "class 1: " << class1.dept << " " << class1.class_number << endl;
}