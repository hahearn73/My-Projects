// Harry Ahearn 2/15/21
// yoda.cpp
// purpose: rearrange 4 input words backwards

#include <iostream>
using namespace std;

int main() {
  
  //input strings
  string firstWord; 
  string secondWord;
  string thirdWord;
  string fourthWord;
  
  cout << "Type in four words: ";  // ask for words
  cin >> firstWord; // receive input 1
  cin >> secondWord; // receive input 2 
  cin >> thirdWord; // receive input 3
  cin >> fourthWord; // receive input 4
  
  // print out words back to front
  cout << fourthWord << " " << thirdWord << " " << secondWord << " " <<
  firstWord << endl;
  
  return 0;
}
