/* Harry Ahearn 
 * A class that keeps track of word-frequecy data.
 * Further documentation is in WordFreqLinkedList.cpp
 * 
 * Mark A. Sheldon, Tufts Uiversity, Spring 2021
 */


/*******************************************************************
 *    CAUTION:                                                     *
 *    YOU MUST LEAVE MOST OF THIS FILE UNCHANGED.                  *
 *                                                                 *
 *    You may add additional private member functions, but not     *
 *    additional data members.  The member functions must go in    *
 *    the area documented below.  Changing other parts of the file *
 *    may prevent us from being able to grade your work.           *
 *******************************************************************/

#ifndef WORDFREQLINKEDLIST_H
#define WORDFREQLINKEDLIST_H

#include <string>

struct WordFreq {
        std::string word;
        int         freq;
};

class WordFreqLinkedList
{
public:
        WordFreqLinkedList();
        ~WordFreqLinkedList();

        int      size();
        void     countOccurrence(std::string word);
        WordFreq get(int index);

        void     remove(std::string word);

        void     debugPrint();

private:
        struct Node {
                WordFreq  data;
                Node     *next;
        };

        Node *front;          // pointer to first node in list or nullptr
        int   numElements;    // number of elements curretly stored in list

        /*******************************************************************/
        /*   DO NOT CHANGE ANYTHING ABOVE THIS LINE.                       */
        /*   Students MAY add their own private member functions below     */
        /*   this block and above the next comment block.  Do not add data */
        /*   members.                                                      */
        /*******************************************************************/
        // Add any private member functions here:


        Node *newNode(std::string word, int n, Node *next);
        void makeList(std::string word);
        void removeFirst();


        /*******************************************************************/
        /*              Students MAKE NO CHANGES BELOW HERE                */
        /*******************************************************************/
        
        friend class WordFreqLinkedListTester;  // A friend class for testing

        /* 
         * Making copy constructor and assignment operator private
         * to prevent their inadvertant use from compiling.
         * Students do NOT implement these
         */
        WordFreqLinkedList(WordFreqLinkedList &other);
        WordFreqLinkedList &operator=(WordFreqLinkedList &rhs);
};

#endif
