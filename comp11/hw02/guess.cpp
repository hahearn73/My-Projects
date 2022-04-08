/*
 * guess.cpp
 * 
 * Harry Ahearn 2/19/21
 * 
 * purpose: make a random integer that the user has 3 chances to guess
 *          after each guess, tell the user if they were too high or too low
 */

#include <iostream>

// The following are for srand() and time()
// for random numbers. Leave them 
// in your program.
#include <cstdlib>
#include <ctime>

using namespace std;
 
int main()
{
        // Leave the following line as the first line of main.
        // Do not call srand() again.  This is enough to enable
        // you to get a different random number each time you
        // call the program
        srand(time(nullptr));

        // Put the rest of your main here:

        // random integer
        int n = rand();
        n %= 11;
        n += 5;
        int guess; // input variable
        
        // round 1
        cout << "Enter a guess: ";
        cin >> guess;
        
        // round 2
        if (guess > n) {
            cout << "That was too high. Enter a guess: ";
            cin >> guess;
        }
        else if (guess < n) {
            cout << "That was too low. Enter a guess: ";
            cin >> guess;
        }
        else {
            cout << "You guessed it! Good job!" << endl;
            return 0; // end program if guess is right
        }
        
        // round 3
        if (guess > n) {
            cout << "That was too high. Enter a guess: ";
            cin >> guess;
        }
        else if (guess < n) {
            cout << "That was too low. Enter a guess: ";
            cin >> guess;
        }
        else {
            cout << "You guessed it! Good job!" << endl;
            return 0; // end program if guess is right
        }
        
        if(guess == n) {
            cout << "You guessed it! Good job!" << endl;
        }
        else {
            cout << "The number was " << n << ". "; 
            cout << "Better luck next time!" << endl;
        }
        
        return 0;
}
