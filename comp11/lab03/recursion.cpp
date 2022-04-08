// Harry Ahearn 2/24/21

// purpose: create recursion methods to demonstrate a command of recursion

#include <iostream>
using namespace std;

int multiply(int x, int y);
int power(int x, int k);
int sum_from(int a, int b);
// int double_digit(int n);

int main() {
    
    cout << power(2, 3) << endl;
    cout << multiply(8,8) << endl;
    cout << sum_from(20, 26) << endl;
    
}

/*
 * int multiply
 * purpose: multiplies two numbers
 * parameters: the two numbers
 * returns: the multiplaction of the two numbers
 */
int multiply(int x, int y) {
    if(y == 1) {
        return x;
    }
    else if(y == 0 || x == 0) {
        return 0;
    }
    return x + multiply(x, y - 1);
}

/*
 * int power
 * purpose - computes an exponential operation
 * parameters - integer and its power
 * returns - the integer x to the power k
 * requirements - both integers are not 0
 */
int power(int x, int k) {
    if(k == 1) {
        return x;
    }
    else if(k == 0) {
        return 1;
    }
    else if(x == 0){
        return 0;
    }
    else if(x == 1) {
        return 1;
    }
    return x * power(x, k - 1);
}

/*
 * int sum_from
 * purpose - compute the sum of all numbers between 2 points
 * parameters - starting and end integers
 * returns - the sum of all numbers between 2 points
 */
int sum_from(int a, int b) {
    if(a == b) {
        return b;
    }
    return a + sum_from(a + 1, b);
}
