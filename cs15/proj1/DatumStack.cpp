/* Harry Ahearn 10/26/21 CalcYouLater DatumStack.cpp
This file is the implementation of the DatumStack interface. It is essentially
a wrapper class for the vector that is a private member variable of the
DatumStack class as most functions just call functions used by the vector class
*/

#include "DatumStack.h"
#include <stdexcept>

/*
 * default constructor
 * does nothing
 */
DatumStack::DatumStack() {}

/*
 * constructor
 * adds all elements in arr to the stack
 */
DatumStack::DatumStack(Datum *arr, int size)
{
    for (int i = 0; i < size; i++)
        stack.push_back(arr[i]);
}

/*
 * isEmpty
 * returns true if stack is empty, false otherwise
 */
bool DatumStack::isEmpty()
{
    return stack.empty();
}

/*
 * clear
 * clears stack
 */
void DatumStack::clear()
{
    stack.clear();
}

/*
 * size
 * returns number of elements in stack
 */
int DatumStack::size()
{
    return stack.size();
}

/*
 * top
 * returns top Datum object in stack
 */
Datum DatumStack::top()
{
    if (isEmpty()) 
        throw std::runtime_error("empty_stack");
    return stack.back();
}

/*
 * pop 
 * deletes last element in stack
 */
void DatumStack::pop()
{
    if (isEmpty()) 
        throw std::runtime_error("empty_stack");
    stack.pop_back();
}

/*
 * push
 * adds d to the stack
 */
void DatumStack::push(Datum d)
{
    stack.push_back(d);
}