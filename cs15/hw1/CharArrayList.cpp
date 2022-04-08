/*
 * CharArrayList.cpp
 * 
 * COMP 15 homework 1
 * by C.R. Calabrese, January 2021
 * edited by Harry Ahearn, 9/17/21
 * 
 * Stores characters in a certain order. It imitates some functions of the
 * C++ string. 
 * 
 * Notes: this implementation uses a dynamic array. So, potential
 * drawbacks as compared to the CharLinkedList class include slower insertions
 * and removals at the front of the list. On the other hand, since only one
 * pointer variable is needed for the entire list (as opposed to one pointer
 * per element in the CharLinkedList), the CharArrayList class has the
 * advantage of more efficient memory usage over the CharLinkedList.
 */

#include "CharArrayList.h"

// for print
#include <iostream>

using namespace std;

/* Purpose: initializes an empty CharArrayList */
CharArrayList::CharArrayList()
{
    len  = 0;
    cap  = 0;
    data = nullptr;
}

/*    Purpose: initializes a CharArrayList containing one character
 * Parameters: the character that should be stored in the new list
 */
CharArrayList::CharArrayList(char c)
{
    len = 1;
    cap = 1;
    data = new char[cap];
    data[0] = c;
}

/*    Purpose: initializes a CharArrayList containing all of the specified 
 *             characters, in the given order
 * Parameters: An array (in order) of characters to be stored in the list;
 *             the length of the given array (as an int)
 */
CharArrayList::CharArrayList(char *arr, int size)
{
    len = 0;
    cap = 0;
    data = nullptr;
    for (int i = 0; i < size; i++)
        pushAtBack(arr[i]);
    delete [] arr;
}

/* Purpose: copy constructor -- creates a list with the same information as
 *          the one passed in
 * 
 *    Note: The array capacity may be different from the capacity of the list
 *          that is copied from. That is fine. What is important is that both
 *          lists will store the same information -- to the client, they will
 *          be the same.
 */
CharArrayList::CharArrayList(const CharArrayList &other) 
{
    len = 0; // start with an empty list
    cap = 0;
    data = nullptr;

    // push each item from the other list onto this one
    for (int i = 0; i < other.size(); i++)
        pushAtBack(other.elementAt(i));
}

/* Purpose: destructor -- frees all memory associated with the list */
CharArrayList::~CharArrayList()
{
    delete [] data;
}

/* Purpose: assignment operator -- makes the current list contain the same
 *          information as the one on the right hand side
 * 
 *    Note: The array capacity may be different from the list that is being
 *          copied from.
 */
CharArrayList &CharArrayList::operator =(const CharArrayList &rhs) 
{
    if (this != &rhs) {
        clear(); // clear the current list
        
        // add each element from the other list into this one
        for (int i = 0; i < rhs.size(); i++) {
            pushAtBack(rhs.elementAt(i));
        }
    }
    return *this;
}

/* isEmpty
 *    Purpose: Check if the list is empty
 * Parameters: none
 *    Returns: a boolean -- true if the list is empty, false if it isn't
 * 
 *       Note: "empty" refers to if the client is currently storing any
 *             information in the list. The capacity of the ArrayList is
 *             irrelevant.
 */
bool CharArrayList::isEmpty() const 
{
    return size() == 0;
}

/* size
 *    Purpose: Get the number of characters being stored in the list
 * Parameters: none
 *    Returns: The number of characters currently stored in the list, as an
 *             int (but will never be negative)
 */
int CharArrayList::size() const 
{
    return len;
}

/* first
 *    Purpose: Get the first element in the list.
 * Parameters: none
 *    Returns: The first element in the list, as a char.
 * 
 *       Note: Prints an error and exits if the list is empty.
 */
char CharArrayList::first() const 
{
    if (isEmpty()) {
        cerr << "Cannot get the first element of an empty list" << endl;
        exit(EXIT_FAILURE);
    }
    return data[0];
}

/* last
 *    Purpose: Get the last element in the list.
 * Parameters: none
 *    Returns: The last element in the list, as a char.
 * 
 *       Note: prints an error and exits if the list is empty.
 */
char CharArrayList::last() const 
{
    if (isEmpty()) {
        cerr << "Cannot get the last element of an empty list" << endl;
        exit(EXIT_FAILURE);
    }
    return data[len - 1];
}

/* elementAt
 *    Purpose: Get the character at a given position.
 * Parameters: The index to be accessed, as an int. Should be in bounds; in 
 *             other words, should be in the range [0, size() )
 *    Returns: The element at the specified index, as a char
 *
 *       Note: prints an error and exits if given index is out of range.
 */
char CharArrayList::elementAt(int idx) const
{
    if (idx < 0 || idx >= len) { // checks for range
        cerr << "index " << idx << " not in range [0.." << size() 
            << ")" << endl;
        exit(EXIT_FAILURE); // exits
    }
    return data[idx];
}

/* print
 *    Purpose: Prints the list to the terminal (cout)
 * Parameters: None
 *    Returns: None
 * 
 */
void CharArrayList::print() const
{
    cout << "[CharArrayList of size " << size() <<  " <<";
    for (int i = 0; i < size(); i++) 
            cout << elementAt(i);
    cout << ">>]" << endl;
}

/* clear
 *    Purpose: Makes the list empty
 * Parameters: None
 *    Returns: None
 */
void CharArrayList::clear() 
{
    len = 0;
    cap = 0;
}

/* pushAtBack
 *    Purpose: Adds a character to the back of the list
 * Parameters: The character to be added to the list
 *    Returns: None
 */
void CharArrayList::pushAtBack(char c)
{
    if (len == cap)
        expand();
    data[len] = c;
    len++;
}

/*
 * expand
 * expands the array within the arraylist by 2*cap + 2 and preserves data
 */
void CharArrayList::expand()
{
    cap = cap * 2 + 2; // double + 2
    char *new_data = new char[cap]; // placeholder
    
    for (int i = 0; i < len; i++) 
        new_data[i] = data[i]; // make placeholder = to data
        
    delete [] data; // delete data
    data = new_data; // make data = placeholder
}

/* pushAtFront
 *    Purpose: Adds a character to the front of the list
 * Parameters: The character to be added to the list
 *    Returns: None
 */
void CharArrayList::pushAtFront(char c)
{
    if(len == cap)
        expand();
        
    char *new_data = new char[cap];
    for (int i = 0; i < len; i++) 
        new_data[i + 1] = data[i]; // new AL is data shifted right by 1
    delete [] data;
    new_data[0] = c; // insert c at front
    data = new_data; 
    len++;
}

/* insertAt
 *    Purpose: Adds a character to the list at a given position
 * Parameters: The character to be added to the list and the position at which
 *             it should be added. The position should be in-bounds, that is,
 *             in the range [0, size()]. Providing size() as the index will
 *             insert the character at the back of the list.
 *    Returns: None
 *
 *       Note: prints an error and exits if given index is out of range.
 */
void CharArrayList::insertAt(char c, int idx)
{
    if (idx < 0 || idx > len) { // checks for range
        cerr << "index " << idx << " not in range [0.." << size() << "]" 
            << endl;
        exit(EXIT_FAILURE); // exits
    }
    
    cap++; // premepitvely increase because inserting a new element
    char *new_data = new char[cap];
    
    for (int i = 0; i < len; i++) {
        new_data[i] = data[i]; // make arrays equal
        if (i >= idx) // if past idx
            new_data[i+1] = data[i]; // shift everything over 1
    }
    
    new_data[idx] = c; // insert new value
    len++; // increase size because new value was added
    delete [] data; // recycle
    data = new_data;
}

/* popFromFront
 *    Purpose: Removes the first element from the list
 * Parameters: None
 *    Returns: None
 *
 *       Note: Prints an error message and quits if the list is empty
 */
void CharArrayList::popFromFront()
{
    // confirm list is non-empty
    if (isEmpty()) {
        cerr << "Cannot pop from an empty list" << endl;
        exit(EXIT_FAILURE);
    }
    removeAt(0);
}

/* popFromBack
 *    Purpose: Removes the last element from the list
 * Parameters: None
 *    Returns: None
 * 
 *       Note: Prints an error message and exits if the list is empty
 */
void CharArrayList::popFromBack()
{
    // confirm list is non-empty
    if (isEmpty()) {
        cerr << "Cannot pop from an empty list" << endl;
        exit(EXIT_FAILURE);
    }
    removeAt(size() - 1);
}

/* removeAt
 *    Purpose: Removes the element at a given index
 * Parameters: The position at which to remove an element, which should be the
 *             index of an element currently in the list; in other words,
 *             should be in the interval [0, size)
 *    Returns: None
 * 
 *       Note: If the amount of space in the array that is in use drops to less 
 *             than one fourth, the array should be shrunk to half its size.
 */
void CharArrayList::removeAt(int idx)
{
    // confirm index is in range
    if (idx < 0 or idx >= size()) {
        cerr << "index " << idx << " not in range [0.." << size() << ")"
             << endl;
        exit(EXIT_FAILURE);
    }
    // remove the element by shifting all subsequent elements to the left
    for (int i = idx; i < size() - 1; i++) 
        data[i] = data[i + 1];
    len--; // update the length

    if (len <= cap / 4) // shrink array
        cap/=2;
}

/* replaceAt
 *    Purpose: Replaces the element at the given index with the given value
 * Parameters: A character to put in the list and the index of the
 *             element to replace. The index should be in-bounds, in the
 *             range [0, size() )
 * 
 *       Note: Prints an error message and exits if the index is out of bounds
 */
void CharArrayList::replaceAt(char c, int idx)
{
    // confirm index is in range (given code)
    if (idx < 0 or idx >= size()) {
        cerr << "index " << idx << " not in range [0.." << size() << ")"
             << endl;
        exit(EXIT_FAILURE);
    }
    data[idx] = c;    
}

/* concatenate
 *    Purpose: Adds the contents of a CharArrayList to the back of the current 
 *             one.
 * Parameters: A CharArrayList whose contents should be pushed to the back of
 *             the current list. Will not be altered
 *    Returns: None
 */
void CharArrayList::concatenate(const CharArrayList &other)
{
    for (int i = 0; i < other.size(); i++)
        pushAtBack(other.elementAt(i));
}
