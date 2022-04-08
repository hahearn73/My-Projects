/*
 * Preliminary program that reads in the standard input one whitespace 
 * delimited string at a time and prints the lowercase version of those 
 * that begin with a letter.
 * 
 * Only works for ASCII --- Real text is hard!
 *
 * Name: Harry Ahearn
 * Date: 4/19/21
 * Notes:
 */
/*************  Put your program below  *************/

#include <iostream>
using namespace std;

string toLowerCase(string str);

/*
 * purpose:   loops thru a series of characters separated by whitespace and 
 *            prints them out with lowercase letters and symbols only if they 
 *            begin with a letter
 * args:      none
 * returns:   0 when program is finished
 * notes:     calls toLowerCase as a separate function
 */
int main() {
        while (!cin.eof()) {
                string str;
                cin >> str; // input string
                
                // if first character is a letter (AKA if word is a valid word)
                if ((str[0] >= 65 && str[0] <= 90) || 
                        (str[0] >= 97 && str[0] <= 122)) { 
                        cout << toLowerCase(str) << endl; // print lowercase
                }
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
