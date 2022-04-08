/* Harry Ahearn DatumStack_test.cpp 10/26/21 CalcYouLater
The purpose of this file is to test the DatumStack class by calling its 
functions with known inputs and outputs and comparing them to the output 
actually given by the functions.
*/

#include "DatumStack.h"
#include "Datum.h"
#include <iostream>
using namespace std;

/* main 
 * creates a DatumStack and performs tests on it
 */
int main() {
    // test constructors and isEmpty
    DatumStack s;
    if (!s.isEmpty()) cerr << "err" << endl;
    Datum data[2] = {Datum(5), Datum(true)};
    DatumStack d(data , 2);
    if (d.isEmpty()) cerr << "err" << endl;
        
    // test size, top, push, clear
    s.push(Datum(5));
    Datum testDatum(5); // used for comparison with top()
    if (!(s.top() == testDatum)) cerr << "err" << endl;
    if (s.size() != 1) cout << "err" << endl;
    s.clear();
    if (!s.isEmpty()) cout << "err" << endl;
    
    // test pop
    d.pop();
    if (!(d.top() == testDatum)) cerr << "err" << endl;
    if (d.size() != 1) cerr << "err" << endl;
    
    /* should throw errors
    DatumStack emptyStack;
    emptyStack.top();
    emptyStack.pop();
    */
    
    return 0;
}