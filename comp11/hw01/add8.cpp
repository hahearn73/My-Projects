// Harry Ahearn 2/15/21
// add8.cpp
// purpose: receive 8 floating point numbers from, sum them and report them
// to user

#include <iostream>
using namespace std;

int main() {
  float total = 0; // var which holds total
  float input = 0; // var which holds new input
  
  cout << "Enter a floating point number: " << endl; 
  cin >> input; // store input
  total += input; // add input to total
  
  cout << "Enter a floating point number: " << endl; 
  cin >> input; // store input
  total += input; // add input to total
  
  cout << "Enter a floating point number: " << endl; 
  cin >> input; // store input
  total += input; // add input to total
  
  cout << "Enter a floating point number: " << endl; 
  cin >> input; // store input
  total += input; // add input to total
  
  cout << "Enter a floating point number: " << endl; 
  cin >> input; // store input
  total += input; // add input to total
  
  cout << "Enter a floating point number: " << endl; 
  cin >> input; // store input
  total += input; // add input to total
  
  cout << "Enter a floating point number: " << endl; 
  cin >> input; // store input
  total += input; // add input to total
  
  cout << "Enter a floating point number: " << endl; 
  cin >> input; // store input
  total += input; // add input to total  
  
  cout << "The sum is: " << total << endl; // print sum
  
  return 0;
}
