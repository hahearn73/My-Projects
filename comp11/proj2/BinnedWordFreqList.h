/*
 * A class that keeps track of word-frequecy data.
 * Further documentation is in BinnedWordFreqList.cpp
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

#ifndef BINNEDWORDFREQLIST_H
#define BINNEDWORDFREQLIST_H

#include <string>

#include "WordFreqLinkedList.h"

class WordFreqList
{
public:
        WordFreqList();
        ~WordFreqList();

        int      size();
        void     countOccurrence(std::string word);
        WordFreq get(int index);

        void     debugPrint();

private:
        static const int NUM_BINS = 26;

        WordFreqLinkedList wflists[NUM_BINS];

        /*******************************************************************/
        /*   DO NOT CHANGE ANYTHING ABOVE THIS LINE.                       */
        /*   Students MAY add their own private member functions below     */
        /*   this block and above the next comment block.  Do not add data */
        /*   members.                                                      */
        /*******************************************************************/
        // Add any private member functions here:








        
        /*******************************************************************/
        /*              Students MAKE NO CHANGES BELOW HERE                */
        /*******************************************************************/
        
        friend class BinnedWordFreqTester;  // A friend class for testing

        /* 
         * Making copy constructor and assignment operator private
         * to prevent their inadvertant use from compiling.
         * Students do NOT implement these
         */
        WordFreqList(WordFreqList &other);
        WordFreqList &operator=(WordFreqList &rhs);
};

#endif
