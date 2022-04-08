/* Harry Ahearn 10/26/21 CalcYouLater DatumStack.h
This file is the interface for the DatumStack class. It shows that this class
has a default constructor and a constructor that takes in an array of Datum 
to be added to the stack and the size of the array. This interface also shows
that the data storing is done by using a private vector of type Datum.
*/

#ifndef _DATUMSTACK_H_
#define _DATUMSTACK_H_
#include "Datum.h"
#include <vector>

class DatumStack {
public:
    DatumStack();
    DatumStack(Datum *arr, int size);
    
    bool isEmpty();
    void clear();
    int size();
    Datum top();
    void pop();
    void push(Datum d);
    
private:
    std::vector<Datum> stack;
};

#endif