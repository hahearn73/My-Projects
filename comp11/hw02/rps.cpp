/*
 * Harry Ahearn 2/19/21
 * rps.cpp
 * 
 * purpose: play rock-paper-scissors against the computer and output the result
 *          and what the computer picked
 *
 * [Student should fill in the header as per the style guide]
 */

#include <iostream>

// The following are for srand() and time()
// for random numbers. Leave them 
// in your program.
#include <cstdlib>
#include <ctime>

using namespace std;
 
string lossOutput(string str);
string winOutput(string str);

int main()
{
        // Leave the following line as the first line of main.
        // Do not call srand() again.  This is enough to enable
        // you to get a different random number each time you
        // call the program
        srand(time(nullptr));

        // Put the rest of your main here:
        int n = rand();
        n %= 3;
        
        string strLong; // fully written out computer pick ie "paper"
        string strShort; // one letter computer pick ie "p"
        string user;
        
        // creating two computer pick strings saves from needing if/else
        // statements later in the program for comparison as the user
        // will input a letter while the computer must output a full word

        if(n == 0) {
            strLong = "rock";
            strShort = "r";
        }
        else if (n == 1) {
            strLong = "paper";
            strShort = "p";
        }
        else {
            strLong = "scissors";
            strShort = "s";
        }
        
        cout << "Enter rock (r), paper (p), or scissors (s): ";
        cin >> user;
        
        // convert input to lowercase
        if (user == "R") {
            user = "r";
        }
        else if (user == "S") {
            user = "s";
        }
        else if (user == "P") {
            user = "p";
        }


        // if computer and user match input
        if (strShort == user) {
            cout << "It's a tie. The computer also chose " << strLong << ".\n";
        }
        else {
            
            // user input rock
            if (user == "r") { 
                if (strShort == "p") { // computer pick paper
                    cout << lossOutput(strLong);
                }
                else { // computer pick scissors
                    cout << winOutput(strLong);
                }
            }
            
            // user inputs paper
            else if (user == "p") { 
                if (strShort == "r") { // computer pick rock
                    cout << winOutput(strLong);
                }
                else { // computer pick scissors
                    cout << lossOutput(strLong);
                }
            }
            
            // user input scissors
            else if (user == "s"){ 
                if (strShort == "r") { // computer pick rock
                    cout << lossOutput(strLong);
                }
                else { // computer pick paper
                    cout << winOutput(strLong);
                }
            }
        }
        
        return 0;
}

/*
 * lossOutput
 * parameters: computer's pick
 * purpose: gives a string that contains the loss message
 * returns: unique loss message based on computer's pick
 */
string lossOutput(string str) {
    return "You lost. The computer chose " + str + ".\n";
}

/*
 * winOutput
 * parameters: computer's pick
 * purpose: gives a string that contains a loss message
 * returns: unique win message based on computer's pick
 */
 string winOutput(string str) {
     return "You won! The computer chose " + str + ".\n";
 }
