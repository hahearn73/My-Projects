//
// namelist1.h -- A dynamically allocated array with fixed size
//
#ifndef NAMELIST_H
#define NAMELIST_H

#include <iostream>
using namespace std;

class NameList {
public:
        NameList(int capacity);          // Constructor
                                         //  args: capacity of the NameList
        ~NameList();                     // Destructor

        bool   add(string val);          // Adds element to end of array
        int    getCount();               // how many names are in the list
        string getValAt(int index);      // Returns element at the given index
        bool   setValAt(string val, int index); // set value at given index
                                                // Index must be less
                                                // than current size of the 
                                                // NameList object
        void   print();                 // prints current namelist
        void   revprint();              // prints current namelist in reverse
        bool   readFromFile(string);    // reads from named file
        void   readFromCin();           // read from cin

private:

        int     capacity;     // Current capacity of the NameList
        int     n_elements;   // Number of elements stored in the list
        string *data;         // ptr to array of data
};

#endif
