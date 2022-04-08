/* Harry Ahearn 10/26/21 CalcYouLater parser.cpp
This file contains the function parseRString which takes in an istream reference
and stores all characters received in a string until the open braces and closed
braces match. Once that point is reached, the string is returned. If the braces 
never match and the istream reaches eof, a runtime error is thrown
*/

 #include <stdexcept>
 #include <sstream>
 #include <iostream>
 #include <string>
 using namespace std;
 
 /*
  * parseRString
  * takes in istream 
  * returns string from istream once braces are correct, throws error if never 
  * correct
  */
 std::string parseRString (std::istream &input) 
 {
     std::string ret = "{"; // make return string
     int openBrace = 1; // set to 1 because string is initialized with 1 {
     int closeBrace = 0; // brace counters
     while (!input.eof()) { 
         ret = ret + " ";
         std::string newStr;
         input >> newStr;
         ret = ret + newStr;
         if (newStr == "}") closeBrace++;
         if (newStr == "{") openBrace++;
         if (openBrace == closeBrace) return ret; // return if braces match
     }
     throw std::runtime_error("Braces do not match");
 }
 
 // testing of function
 // int main()
 // {
 //     string str1 = " 1 2 + }";
 //     string str2 = " 1 { 4 2 / } / }";
 //     std::istringstream ex1(str1);
 //     std::istringstream ex2(str2);
 //     cout << parseRString(ex1) << "\n" << parseRString(ex2) << endl;
 // 
 //     string str3 = " 55 + } }";
 //     std::istringstream ex3(str3);
 //     cout << parseRString(ex3) << endl;
 // 
 //     /* throws error
 //     string str4 = " 1  + ";
 //     std::istringstream ex4(str4);
 //     cout << parseRString(ex4) << endl;
 //     */
 // 
 //     return 0;
 // }
