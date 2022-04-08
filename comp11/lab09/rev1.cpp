// rev1.cpp Harry Ahearn
// Read in words, reverse, print
//  Shows: dynamically allocated array

#include <iostream>

#include "namelist1.h"

using namespace std;

int main() 
{
        int    num;
        string filename;

        cout << "What size namelist? ";
        cin  >> num;

        NameList list(num);

        cout << "Read from what file? 
        cin  >> filename;

        list.readFromFile(filename);
        list.revprint();

        return 0;
}
