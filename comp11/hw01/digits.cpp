// Harry Ahearn 2/15/21
// digits.cpp
//      purpose: report number of digits in an integer
//        shows: use of output, input, conditional statements
//
//  modified by: Harry Ahearn
//         date: 2/15/21
//

#include <iostream>

using namespace std;

int main()
{
        int input;

        cout << "Enter a number: ";
        cin  >> input;

        bool isNegative = false; // shows whether input is negative or not
        if (input < 0) {
          isNegative = true; // changes to true if input < 0
          input *= -1; // changes input to a positive number
        }

        if (input >= 100) {
                cout << "input has three or more digits" << endl;
        } else if ( input >= 10) {
                cout << "input has two digits" << endl;
        } else if ( input >= 0) {
                cout << "input has one digit" << endl;
        }
        
        if (isNegative) {
          cout << "and input is negative" << endl;
        }

        return 0;
}
