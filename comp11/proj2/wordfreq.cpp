/*
 * wordfreq
 *
 * 1. Reads in strings from the standard input (cin)
 *    Ignores non-words (where a "word" is a sequence of non-whitespace
 *    characters beginnig with an upper or lowercase letter
 * 2. Converts each word to lower case
 * 3. Inserts each word into a WordFreqList to track the number of
 *    times each word is seen

 * 4. When the input is fully processed, prints a line for each word
 *    in the WordFreqList formatted thus:
 *    the interger number of occurrences of the word, a single space,
 *    the word itself, a newline.  E. g., "14 we\n"
 *
 * Only works for ASCII --- Real text is hard!
 *
 * 
 * You may define functions as you see fit.  
 * If you do, you must pass any WordFreqList by reference or using a
 * pointer --- you cannot pass it by value.
 *
 *
 * Mark A. Sheldon, Tufts University, Spring 2021
 *
 *
 * Student name: Harry Ahearn
 * Date: 4/28/2021
 *
 * Anything else you would like to include
 */

#include <iostream>
#include <string>
#include <cctype>

// The following file will be a copy of the file you want
// DON'T CHANGE THIS!
#include "WordFreqList.h"
// Seriously, Don't change the line above.  It's important!

using namespace std;

/*************  Put your program below  *************/

string toLowerCase(string str);

/*
 * purpose:   accepts words from terminal and adds them to a linked list
 * args:      
 * returns:   0 if working
 */
int main() {
        WordFreqList n;
        while (!cin.eof()) {
                string str;
                cin >> str; // input string
                
                // if first character is a letter (AKA if word is a valid word)
                if ((str[0] >= 65 && str[0] <= 90) || 
                (str[0] >= 97 && str[0] <= 122)) { // make lowercase and add 
                        n.countOccurrence(toLowerCase(str)); 
                } // skipped if not valid word
        }   
        // print out            
        for (int i = 0; i < n.size(); i++) {
                cout << n.get(i).freq << " " << n.get(i).word << "\n";
        }
        
        return 0;
}

/*
 * purpose:   converts a string's uppercase letters to lowercase letters
 * args:      the string that is being converted
 * returns:   the string with only symbols and lowercase letters
 * examples:  WORDS => words, W*ords => w*ords, WEFDSFasdfasf8 = wefdsfasdfasf8
 * notes:     this function does not check if the word is a valid word 
 */
string toLowerCase(string str) {
        for (size_t i = 0; i < str.length(); i++) {
                if (str[i] >= 65 && str[i] <= 90) { // if uppercase
                        str[i] += (97 - 65); // convert to lowercase
                }
        }
        return str;
}