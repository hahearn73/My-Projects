/* 
 * CharLinkedList.cpp
 * 
 * COMP 15 homework 1
 * by C.R. Calabrese, January 2021
 * edited by Harry Ahearn, 9/28/21
 * 
 * Stores characters in a certain order. It imitates some functions of the
 * C++ string. 
 * 
 * NOTE: This is implemented using a doubly-linked list. It is not circular
 *       and does not have a "back" pointer.
 */

#include "CharLinkedList.h"

// for the print function
#include <iostream>

using namespace std;

/* Purpose: initializes an empty CharLinkedList */
CharLinkedList::CharLinkedList()
{
    len = 0;
    head = nullptr;
    tail = nullptr;
}

/*    Purpose: initializes a CharLinkedList containing one character
 * Parameters: the character that should be stored in the new list
 */
CharLinkedList::CharLinkedList(char c)
{
    len = 0;
    head = nullptr;
    tail = nullptr;
    pushAtFront(c); // add c to LL
}

/*    Purpose: initializes a CharLinkedList containing all of the specified 
 *             characters, in the given order
 * Parameters: An array (in order) of characters to be stored in the list;
 *             the length of the given array (as an int)
 */
CharLinkedList::CharLinkedList(char *arr, int size)
{
    len = 0;
    head = nullptr;
    tail = nullptr;
    for (int i = 0; i < size; i++) 
        pushAtBack(arr[i]);
    delete [] arr;
}

/* Purpose: copy constructor -- creates a list with the same information as
 *          the one passed in
 */
CharLinkedList::CharLinkedList(const CharLinkedList &other) 
{
    len = 0;
    head = nullptr;
    tail = nullptr;
    for (int i = 0; i < other.size(); i++)
        pushAtBack(other.elementAt(i));
}

/* Purpose: destructor -- frees all memory associated with the list */
CharLinkedList::~CharLinkedList()
{
    Node *curr = head;
    while (curr) {
        Node *next = curr->next;
        delete curr;
        curr = next;
    }
}

/* Purpose: assignment operator -- makes the current list contain the same
 *          information as the one on the right hand side
 */
CharLinkedList &CharLinkedList::operator =(const CharLinkedList &rhs) 
{
    if (this == &rhs)
        return *this;
    for (int i = 0; i < rhs.size(); i++) {
        if (i < len) // if in range, use replace
            replaceAt(rhs.elementAt(i), i);
        else { // if out of range, use pushAtBack
            pushAtBack(rhs.elementAt(i));
        }
    }
    return *this;
}

/* isEmpty
 *    Purpose: Check if the list is empty
 * Parameters: none
 *    Returns: a boolean -- true if the list is empty, false if it isn't
 */
bool CharLinkedList::isEmpty() const 
{
    return size() == 0;
}

/* size
 *    Purpose: Get the number of characters being stored in the list
 * Parameters: none
 *    Returns: The number of characters currently stored in the list, as an
 *             int (will never be negative)
 */
int CharLinkedList::size() const 
{
    return len;
}

/* first
 *    Purpose: Get the first element in the list.
 * Parameters: none
 *    Returns: The first element in the list, as a char.
 * 
 *       Note: Prints an error message and exits if the list is empty.
 */
char CharLinkedList::first() const 
{
    return head->c;
}

/* last
 *    Purpose: Get the last element in the list.
 * Parameters: none
 *    Returns: The last element in the list, as a char.
 * 
 *       Note: Prints an error message and exits if the list is empty.
 */
char CharLinkedList::last() const 
{
    return tail->c;
}

/* elementAt
 *    Purpose: Get the character at a given position.
 * Parameters: The index to be accessed, as an int. Should be in bounds; in 
 *             other words, should be in the range [0, size() )
 *    Returns: The element at the specified index, as a char
 *
 *       Note: prints an error and exits if given index is out of range.
 */
char CharLinkedList::elementAt(int idx) const
{
    if (idx < 0 || idx >= len) { // checks for range
        cerr << "index " << idx << " not in range [0.." << size() << ")" 
            << endl;
        exit(EXIT_FAILURE); // exits
    }
    Node *curr = head;
    for (int i = 0; i < idx; i++) {
        curr = curr->next;
    }
    return curr->c;
}

/* print
 *    Purpose: Prints the list to the terminal (cout)
 * Parameters: None
 *    Returns: None
 */
void CharLinkedList::print() const
{
    cout << "[CharLinkedList of size " << size() << " <<";
    for (Node *curr = head; curr != nullptr; curr = curr->next)
        cout << curr->c;
    cout << ">>]" << endl;
}

/* clear
 *    Purpose: Makes the list empty
 * Parameters: None
 *    Returns: None
 */
void CharLinkedList::clear() 
{
    Node *curr = head;
    while (curr) {
        Node *next = curr->next;
        delete curr;
        curr = next;
    }
    len = 0;
    head = nullptr;
    tail = nullptr;
}

/* pushAtBack
 *    Purpose: Adds a character to the back of the list
 * Parameters: The character to be added to the list
 *    Returns: None
 */
void CharLinkedList::pushAtBack(char c)
{
    if (len == 0) { // special case
        pushAtFront(c);
        return;
    }
    
    Node *new_tail = new Node;
    new_tail->c = c;
    new_tail->prev = tail;
    new_tail->next = nullptr;
    tail->next = new_tail;
    tail = new_tail;

    len++;
}

/* pushAtFront
 *    Purpose: Adds a character to the front of the list
 * Parameters: The character to be added to the list
 *    Returns: None
 */
void CharLinkedList::pushAtFront(char c)
{
    Node *node = new Node;
    node->c = c;
    node->next = head;
    node->prev = nullptr;
    len++;
    
    if (head != nullptr)
        head->prev = node;
    
    head = node;
    if (len == 1) 
        tail = head;
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
 * 
 *      To-Do: Would be fun to figure out how to do this recursively -- prev
 *             pointer makes it a little more complicated
 */
void CharLinkedList::insertAt(char c, int idx)
{
    if (idx < 0 || idx > len) { // checks for range
        cerr << "index " << idx << " not in range [0.." << size() << "]" 
            << endl;
        exit(EXIT_FAILURE); // exits
    }
    
    if (idx == 0) { // special case
        pushAtFront(c);
        return;
    }
    
    Node *curr = head; // node before inserted node
    for (int i = 0; i < idx - 1; i++) 
        curr = curr->next;
    Node *new_node = new Node; // node to be inserted
    new_node->c = c; 
    new_node->prev = curr; // fix relational pointers
    new_node->next = curr->next;
    curr->next = new_node;
    curr->next->prev = new_node; 
    len++;
}

/* popFromFront
 *    Purpose: Removes the first element from the list
 * Parameters: None
 *    Returns: None
 *       Note: Prints an error message and exits if the list is empty
 */
void CharLinkedList::popFromFront()
{
    // confirm list is non-empty
    if (isEmpty()) {
        cerr << "Cannot pop from an empty list" << endl;
        exit(EXIT_FAILURE);
    }
    if (len == 1) {
        clear();
        return;
    }
    Node *curr = head;
    head = curr->next;
    delete curr;
    head->prev = nullptr;
    len--;
}

/* popFromBack
 *    Purpose: Removes the last element from the list
 * Parameters: None
 *    Returns: None
 *       Note: Prints an error message and exits if the list is empty
 */
void CharLinkedList::popFromBack()
{
    // confirm list is non-empty
    if (isEmpty()) {
        cerr << "Cannot pop from an empty list" << endl;
        exit(EXIT_FAILURE);
    }
    if (len == 1) { // 
        clear();
        return;
    }
    Node *new_tail = tail->prev;
    new_tail->next = nullptr;
    delete tail;
    tail = new_tail;
    len--;
}

/* removeAt
 *    Purpose: Removes the element at a given index
 * Parameters: The position at which to remove an element, which should be the
 *             index of an element currently in the list; in other words,
 *             should be in the interval [0, size)
 *    Returns: None
 */
void CharLinkedList::removeAt(int idx)
{
    // confirm index is in range
    if (idx < 0 or idx >= size()) {
        cerr << "index " << idx << " not in range [0.." << size() << ")"
             << endl;
        exit(EXIT_FAILURE);
    }
    
    if (idx == 0) { // special case
        popFromFront();
        return;
    }
    if (idx == len - 1) { // special case
        popFromBack();
        return;
    }
    
    Node *curr = head;
    for (int i = 0; i < idx; i++)
        curr = curr->next;
    curr->prev->next = curr->next; // fix relational pointers
    curr->next->prev = curr->prev;
    delete curr;
    len--;
}

/* replaceAt
 *    Purpose: Replaces the element at the given index with the given value
 * Parameters: A character to put in the list and the index of the
 *             element to replace. The index should be in-bounds, in the
 *             range [0, size() )
 *       Note: Prints an error message and exits if the index is out of bounds
 */
void CharLinkedList::replaceAt(char c, int idx)
{
    // confirm index is in range (given code)
    if (idx < 0 or idx >= size()) {
        cerr << "index " << idx << " not in range [0.." << size() << ")"
             << endl;
        exit(EXIT_FAILURE);
    }
    Node *curr = head;
    for (int i = 0; i < idx; i++)
        curr = curr->next;
    curr->c = c;
}

/* concatenate
 *    Purpose: Adds the contents of a CharLinkedList to the back of the current 
 *             one.
 * Parameters: A CharLinkedList whose contents should be pushed to the back of 
 *             the current list. Will not be altered
 *    Returns: None
 */
void CharLinkedList::concatenate(const CharLinkedList &other)
{
    for (int i = 0; i < other.size(); i++)
        pushAtBack(other.elementAt(i));
}
