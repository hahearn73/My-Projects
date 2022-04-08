// Harry Ahearn
// namelist1.cpp -- A dynamically allocated array with fixed size
//
#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "namelist1.h"

using namespace std;

// -- Initialize a namelist ---
//   args: capacity of the NameList

NameList::NameList(int cap) 
{
        capacity   = cap;
        data       = new string[capacity];
        n_elements = 0;
}

// -- Destroys a namelist ---

NameList::~NameList()
{
        delete [] data;
}

// -- Adds the given element to end of the array ---
//   args: element to be added
//   rets: true if element is successfully added, false otherwise

bool NameList::add(string element)
{
        if (n_elements == capacity)
                return false;
        
        data[n_elements] = element;
        n_elements++;
        return true;
}

// -- reads in data lines from cin until eof
//   args: none
//   does: uses getline(cin,..)
//   errs: if too much data: prints to cerr and calls exit(1)
//
void NameList::readFromCin()
{
        string  line;

        getline(cin, line);
        while (not cin.eof()) {
                if (not add(line)) {
                        cerr << "too much data" << endl;
                        exit(1);
                }
                getline(cin, line);
        }
}
// -- reads in data lines from named file
//   args: name of file as string
//   rets: false if cannot open file
//   does: uses getline(data_source,..)
//   errs: quit if too much data (prints to cerr and calls exit(1)

bool NameList::readFromFile(string filename)
{
        ifstream input;
        string   line;

        input.open(filename.c_str());
        if (not input.is_open())
                return false;

        getline(input, line);
        while (not input.eof()) {
                if (not add(line)) {
                        cerr << "too much data" << endl;
                        exit(1);
                }
                getline(input, line);
        }
        input.close();
        return true;
}


// -- Prints the namelist, in reverse order, one name per line
void NameList::revprint()
{
        for (int i = n_elements - 1; i >= 0; i--)
                cout << data[i] << endl;
}
// -- Prints the namelist, one name per line
void NameList::print()
{
        for (int i = 0; i < n_elements; i++) {
                cout << data[i] << endl;
        }
}

// -- Returns number of items in the NameList ---
//   rets: number of elements in the NameList

int NameList::getCount()
{
        return n_elements;
}

// -- Returns element at the given index ---
//   args: index of the element
//   rets: element at the given index
//   note: SHOULD make sure index in in range

string NameList::getValAt(int index)
{
        return data[index];
}

// -- Places the given element at the given index ---
//   args: element and index
//   rets: true if element is successfully added, false otherwise

bool NameList::setValAt(string element, int index)
{
        // STUB
}
