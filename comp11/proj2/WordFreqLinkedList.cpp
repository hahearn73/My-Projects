/* Harry Ahearn
 * A linked-list based implementation of a class that keeps track of 
 * word-frequecy data.
 * 
 * The data are stored as a singly-linked sequence of nodes accessed
 * from a single pointer (in the data member 'front') to the first
 * node in the list (or the nullptr if the list is empty).  Each node
 * has a word (stored as a string), and an integer representing the
 * number of times that word has been counted.
 *
 * IMPORTANT INVARIANT:
 * The words are in the list in alphabetical order. 
 *
 * Mark A. Sheldon, Tufts Uiversity, Spring 2021
 *
 *
 * Student name: Harry Ahearn
 * Date: 4/19/21 
 *
 * Anything else you would like to include
 */

/*************  Fill in the TODO items below  *************/
/***  You may add additional private member functions   ***/
/**********************************************************/
#include <iostream>
#include <string>
#include <cstdlib>

#include "WordFreqLinkedList.h"

using namespace std;

/*
 * Purpose:  Constructor initializes an empty list
 */
WordFreqLinkedList::WordFreqLinkedList()
{
        numElements = 0;
        front =  nullptr;
}

/*
 * Purpose:  Destructor recycles the space associated with all nodes
 *           in the list
 */
WordFreqLinkedList::~WordFreqLinkedList()
{
        Node *n = front;
        
        while(n != nullptr) {
                Node *x = n->next;
                delete n;
                n = x;
        }
        
        front = nullptr;
}

/*
 * Purpose:  Return the current size of the list, 
 *           i. e., the number of words/nodes in the list
 */
int WordFreqLinkedList::size()
{
        return numElements;
}

/*
 * Purpose:  Register one more occurrence of the given word
 *           If word is already in list, it's frequency is incremented by one
 *           If word is not in list, it is added with a frequency of 1
 *           Words are always added in alphabetical order, that is
 *           adding a new word means it goes in front of the first
 *           word that compares > than the new word, or at the end of
 *           the list if this word comes after all the words in the
 *           list alphabetically.
 * Params:   The string word to be added to the list
 * Effects:  Modifies a frequency in the list or adds a new element
 */
void WordFreqLinkedList::countOccurrence(string word)
{
        if(numElements == 0) {makeList(word); return;} // list is empty
        if (front->data.word > word) { // word goes before list
                front = newNode(word, 1, front); // new word goes in front
                numElements++; 
                return;
        }
        
        Node *curr = front;
        while (curr != nullptr) { // loop thru linked list
                if (curr->data.word == word) { // word found
                        curr->data.freq++; 
                        return;
                }
                if (curr->data.word < word && curr->next != nullptr && 
                                curr->next->data.word > word) { 
                        Node *x = newNode(word, 1, curr->next);
                        curr->next = x;
                        numElements++;
                        return; // this block: if word goes between two words
                }
                if (curr->next == nullptr) { // put at end of list
                        Node *x = newNode(word, 1, nullptr); 
                        curr->next = x;
                        numElements++;
                        return;
                }
                curr = curr->next; // move thru list
        }
}

/*
 * Purpose:   makes a list of exactly size 1
 * args:      word to be put into list
 * returns:   void
 * notes:     does not delete any nodes if called incorrectly
 */
void WordFreqLinkedList::WordFreqLinkedList::makeList(string word) {
        front = newNode(word, 1, nullptr);
        numElements = 1;
        return;
}

/*
 * Purpose:  Return the index-th element of the list
 * Params:   index must be in range [0 .. size) where
 *           size is the number of words stored in the list
 * Effects:  if index is out of range, prints error message and exits program
 *           otherwise, none
 */
WordFreq WordFreqLinkedList::get(int index)
{
        Node *np;
        int count = 0;
        int size = numElements;

        for (np = front; (np != nullptr) and (count < index); np = np->next) {
                count++; 
        } // loop sets np to correct index OR nullptr if out of bounds
        
        if (np == nullptr) { // index out of bounds
                cerr << "index " << index << " out of range [0, " << size<< ")" 
                        << endl;
                exit(1);
        } else { // index in bounds
                return np->data;
        }
}

/*
 * Purpose:  Remove word from the list.  That is, it removes and 
 *           recycles the node containing the word (and its count)
 */
void WordFreqLinkedList::remove(string word)
{
        if (front == nullptr) return; // list is empty
        if (front->data.word == word) { // first word matches
                removeFirst();
                numElements--;
                return;
        }
        
        for (Node *curr = front; curr != nullptr; curr = curr->next) {
                Node *x = curr->next;
                if (x != nullptr && x->data.word == word) { // x exists
                        curr->next = x->next; // curr jumps over x
                        delete x; // x is recycled
                        numElements--;
                        return;
                }
        }
        return;
}

/*
 * Purpose:   removes first node in linked list
 * Args:     
 * returns:   void
 *
 */
void WordFreqLinkedList::removeFirst()
{
        Node *to_delete_p = front;
        if (to_delete_p != nullptr) {
                front = to_delete_p -> next; // front shifts to the next node
                delete to_delete_p; // delete original front node
        }
}

/*
 * Purpose:   makes a new node
 * Args:      the word to be in the node, the frequency, the node it points to
 * Returns:   node
 * 
 */
WordFreqLinkedList::Node *WordFreqLinkedList::newNode(string word, int n, 
        Node *next)
{
        Node *result = new Node;

        result->data.word = word;
        result->data.freq = n;
        result->next = next;

        return result;
}

/*
 * Purpose:  print out the underlying list on cout
 * Effects:  prints to cout
 * Notes:    this function is here for debugging purposes.
 *           It will not be called in the final version of the wordfreq
 *           program.
 *           Still LEAVE IT AS-IS:  WE WILL USE IT FOR TESTING.
 */
void WordFreqLinkedList::debugPrint()
{
        Node *curr = front;

        cout << "[";
        while (curr != nullptr) {
                cout << "{" << curr->data.word << ", "
                     << curr->data.freq << "}";
                if (curr->next != nullptr)
                        cout << ", ";
                curr = curr->next;
        }
        cout << "]";
}
