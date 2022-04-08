//
// namelist2.h -- An ArrayList that grows as data are added
//
#ifndef NAMELIST_H
#define NAMELIST_H

#include <iostream>
using namespace std;

class NameList {
public:
        NameList();                      // Constructor
                                         //  defaults to INIT_SIZE elements
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

        int    getCapacity();           // returns current capacity
        void   ensureCapacity(int newCapacity);  // Makes sure namelist has at 
                                                 // least this capacity, 
                                                 // increasing
                                                 // capacity if needed
private:
        static const int INIT_SIZE = 10;

        int     capacity;     // Current capacity of the NameList
        int     n_elements;   // Number of elements stored the list
        string *data;         // ptr to array of data
};

#endif
