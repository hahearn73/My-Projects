// Harry Ahearn 2/15/21
// make_change.cpp
// purpose: display quantity of quarters, nickels, dimes, pennies based on input
// amount

#include <iostream>
using namespace std;

int main() {
  int change;
  
  cout << "Amount of change in cents: ";
  cin >> change;
  
  int q = change / 25; // how many quarters 
  change -= q * 25; // subtract that amount of quarters
  
  int d = change / 10; // how many dimes
  change -= d * 10; // subtract that amount of dimes
  
  int n = change / 5; // how many nickels 
  change -= n * 5; // subtract that amount of nickels
  
  // NOTE: change is now equal to number of pennies
  cout << q << " quarters, " << d << " dimes, " << n << " nickels, " << change
  << " pennies" << endl; // output quantity of each coin
  
  return 0;
}
