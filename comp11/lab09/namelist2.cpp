// Harry Ahearn
// namelist2.cpp -- An ArrayList that resizes as new elements are added
//
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "namelist2.h"
using namespace std;

//  -- Initialize a namelist with capacity of INIT_SIZE elements --
//  args: none: starts with default initial size

NameList::NameList()
{
        capacity   = INIT_SIZE;
        data       = new string[capacity];
        n_elements = 0;
}

// -- Destroys a namelist --

NameList::~NameList()
{
        delete [] data;
}

// -- Adds the given element to end of the array ---
//   args: element to be added
//   rets: true if element is successfully added, false otherwise

bool NameList::add(string element)
{
        ensureCapacity(n_elements + 1);
        
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
                // TODO: STORE line in namelist and get next line
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

//  Returns capacity of the NameList
//  rets: maximum number of elements that can be stored in the NameList
int NameList::getCapacity()
{
        return capacity;
}

//
//  Makes sure the namelist can hold the given number of elements.
//  If it's big enough do nothing.  Otherwise, increase the size to
//  the maximum of the given newCapacity and (2 * current capacity) + 2
//   args: new capacity of the NameList
//
void NameList::ensureCapacity(int newCapacity)
{
        if (newCapacity == capacity) {
                string *arr = new string[capacity * 2];
                
                for (int i = 0; i < capacity; i++) {
                        arr[i] = data[i];
                }
                
                delete [] data;
                data = arr;
                capacity = capacity * 2;
        }
}
