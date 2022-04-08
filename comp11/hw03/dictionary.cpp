/* Harry Ahearn 2/25/21
 * 
 * dictionary.cpp
 * purpose: output the definition of the requested word
 *
 */
 
 #include <iostream>
 using namespace std;
 
 string getInput();
 string findDefinition(string str);
 void printDefinition(string str);
 
 int main() {
     string s = getInput();
     string definition = findDefinition(s);
     printDefinition(definition);
     return 0;
 }
 
 /*
  * getInput
  * no parameters
  * purpose: receives input from user
  * returns user input as a string
  */
 string getInput() {
     string s;
     cin >> s;
     return s;
 }
 
 /*
  * findDefinition
  * parameters: input string from user
  * purpose: finds if the parameter is in the dictionary
  * returns: the definition or a statement saying the word is not found
  */
string findDefinition(string str) {
    string wordList[] = {"Variable", "Function", "Recursion", "Pseudocode", "Conditional", "Comp11", "Parameter"};
    
    string definitions[7] = {
    "A location in the computer's memory that can store a value", "A named block of code that can be invoked as a statement or within an expression", "A situation in which a definition refers to the term it is defining", "A set of human readable instructions created for the purpose of outlining unwritten code", "A method to execute a block of code depending on the outcome of an expression", "An introductory computer science class at Tufts University", "An input to a function"};
    
    bool flag = true;
    for(int i = 0; i < 7; i++) {
        if(wordList[i] == str) {
            str = definitions[i];
            flag = false;
        }
    }
    
    if (flag) {
        str = "Definition Not Found";
    }
    return str;
}

/*
 * printDefinition
 * parameters: string to be output - the definition of the input word
 * purpose: prints the definition or definition not found
 * void: returns nothing
 */
void printDefinition(string str) {
    cout << str << endl;
}
 