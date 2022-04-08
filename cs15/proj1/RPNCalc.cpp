/* Harry Ahearn 10/26/21 CalcYouLater RPNCalc.cpp
This is the implementation of the RPNCalc interface. This interface designs a 
calculator that uses a stack to simulate how a calculator that reads reverse
polish notation would work. Specifically, this is accomplished using a command 
loop which pushes data onto a stack and executes commands on the top members 
of the stack if a desired input occurs. This calculator can also run some 
more complex commands that a normal calculator could not perform, such as 
reading from a file, performing a basic if else statement, and executing a 
block of commands using an exec function.

The implementation uses a command loop in 
the run function to take in commands. These commands are then passed to a 
wrapper function which calls the correct command based on the input received.
If their is an eof or the user calls quit the run function stops and the RPNCalc
object will stop accepting input. 
*/

#include "RPNCalc.h"
#include "DatumStack.h"
#include "Datum.h"
#include <stdexcept>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
std::string parseRString (std::istream &input); // function from parser.cpp

/* run 
 * purpose: is the command loop for class, catches runtime errors, passes input
 *          to wrapper functions which determine the actual function to call
 * void
 */
void RPNCalc::run()
{
    string input;
    bool flag = true;
    while (flag) {
        try {
            cin >> input;
            flag = simpleCommand(input, cin); // = true if input != quit
        } catch (runtime_error e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
    cerr << "Thank you for using CalcYouLater." << endl;
}

/* simpleCommand
 * handles simple string commands, calls complexCommands if input is not simple
 * returns false if input is "quit" or stream.eof() is true, true otherwise
 * arguments: input is the command string, stream is eof tested, and passed to 
 *            complexCommands if no simple command is executed
 */
bool RPNCalc::simpleCommand(const string& input, istream& stream)
{
    if (stream.eof()) return false;
    if (isNumber(input)) stack.push(Datum(stoi(input)));
    else if (input == "#t" or input == "#f") boolCommand(input); //boolean input
    else if (input == "not") notCommand(); // calls not command
    else if (input == "print") cout << stack.top().toString() << endl; // print
    else if (input == "clear") stack.clear(); // clears stack
    else if (input == "drop") stack.pop(); // pops top of stack
    else if (input == "dup") stack.push(stack.top()); // duplicates top of stack
    else if (input == "swap") swapCommand(); // swaps top two elements of stack
    else if (input == "quit") return false; // quits program
    else if (input == "+" or input == "-" or input == "*" 
        or input == "/" or input == "mod")
        mathOperatorCommand(input); // handles math operator input
    else if (input == "<" or input == ">" or input == "<=" 
        or input == ">=" or input == "==")
        relationalOperatorCommand(input); // handles relational operator input
    else 
        complexCommands(input, stream); // handles complex commands
    return true;
}

/* complexCommands
 * calls function based on given input, gives stream to function if required
 * arguments: input string containing the command, 
 *            stream where data is coming from
 */
void RPNCalc::complexCommands(const string& input, istream& stream)
{
    if (input[0] == '{') {
        RStringCommand(stream);
        return;
    }
    else if (input == "exec") {
        execCommand();
        return;
    }
    else if (input == "file") {
        fileCommand();
        return;
    }
    else if (input == "if") {
        ifCommand();
        return;
    }
    else if (input != "}")
        cerr << input << ": unimplemented" << endl;
}

/* fileCommand
 * accepts commands from file and passes them to simpleCommand
 * void
 */
void RPNCalc::fileCommand()
{
    Datum top = stack.top();
    stack.pop();
    if (!top.isRString()) {
        cerr << "Error: file operand not rstring" << endl;
        return;
    }
    ifstream file;
    string file_name = top.toString().substr(2, top.toString().length() - 4);
    file.open(file_name); // opens string stored in RString at top of stack
    if (not file.is_open()) {
        cerr << "Unable to read " << file_name << endl;
        return;
    }
    string input;
    while (!file.eof()) { // acts as a command loop
        file >> input;
        simpleCommand(input, file); // passes commands to wrapper function
        if (input == "quit")
            exit(EXIT_SUCCESS); // exits if quit is called
    }
}

/* ifCommand
 * pops top 3 datum, pushes top datum onto stack of 3rd datum is false, pushes
 * second datum onto stack if 3rd datum is false, calls execCommand
 * note: requires that stack contains a top 2 datum of RString and a third Datum
 *       of bool
 */
void RPNCalc::ifCommand()
{
    Datum falseRString = stack.top();
    stack.pop();
    Datum trueRString = stack.top();
    stack.pop();
    Datum boolDatum = stack.top();
    stack.pop();
    
    if (!trueRString.isRString() or !falseRString.isRString()) { 
        cerr << "Error: expected rstring in if branch" << endl;
        return; // makes sure top 2 datum are rstrings
    }
    if (!boolDatum.isBool()) { // ensures boolDatum is bool
        cerr << "Error: expected boolean in if test" << endl;
        return;
    }
    
    if (boolDatum.getBool()) // push correpsonding r string onto stack
        stack.push(trueRString);
    else
        stack.push(falseRString);
    execCommand(); // execs top RString on stack
}

/* execCommand
 * executes top RString on stack
 * note: requires that top of stack is an RString
 */
void RPNCalc::execCommand()
{
    if (!stack.top().isRString()) { // not RString
        cerr << "Error: cannot execute non rstring" << endl;
        return;
    }
    string str = stack.top().toString();
    stack.pop();
    str = str.substr(1, str.length());
    istringstream stream(str);
    string input;
    while (!stream.eof()) { // acts as a command loop
        stream >> input;
        simpleCommand(input, stream);
        if (input == "quit") { // exit program
            cerr << "Thank you for using CalcYouLater." << endl;
            exit(EXIT_SUCCESS); // success to return 0
        }
    }
}

/* RStringCommand
 * Parses given stream to a string and pushes onto stack
 * Arguments: stream is the stream where data is coming from
 */
void RPNCalc::RStringCommand(istream& stream)
{
    string str = parseRString(stream);
    stack.push(Datum(str));
}

/* boolCommand
 * pushes true onto stack if input is "#t" and false otherwise
 * Arguments: input is the string containing #t or #f
 * Note: should only be called if input is "#t" or "#f"
 */
void RPNCalc::boolCommand(const string& input)
{
    if (input == "#t")
        stack.push(Datum(true));
    else
        stack.push(Datum(false));
}

/* swapCommand
 * swaps top two elements in stack
 * Note: requires stack to be >= size of 2
 */
void RPNCalc::swapCommand()
{
    Datum temp1 = stack.top();
    stack.pop();
    Datum temp2 = stack.top();
    stack.pop();
    stack.push(temp1);
    stack.push(temp2);
}

/* notCommand 
 * changes top element's bool value
 * Note: requires top datum to be a bool datum
 */
void RPNCalc::notCommand()
{
    Datum temp = stack.top();
    stack.pop();
    stack.push(Datum(!temp.getBool()));
}

/* mathOperatorCommand
 * performs operation given by input on top two datum given, pushes to stack
 * Argument: input is the string containing the desired operation
 *  Note: requires top 2 datum to be int datums
 */
void RPNCalc::mathOperatorCommand(const string& input)
{
    Datum topDatum = stack.top();
    stack.pop();
    Datum deeperDatum = stack.top();
    stack.pop();
    if (input == "+")
        stack.push(Datum(deeperDatum.getInt() + topDatum.getInt())); // adds
    else if (input == "-")
        stack.push(Datum(deeperDatum.getInt() - topDatum.getInt())); // subtract
    else if (input == "*")
        stack.push(Datum(deeperDatum.getInt() * topDatum.getInt())); // times
    else if (input == "/") {
        if (topDatum.getInt() == 0) {
            cerr << "Error: division by 0." << endl;
            return;
        }
        stack.push(Datum(deeperDatum.getInt() / topDatum.getInt())); // divides
    }
    else if (input == "mod") 
        stack.push(Datum(deeperDatum.getInt() % topDatum.getInt())); // mod
}

/* relationalOperatorCommand
 * performs operation given by input on top two datum given, pushes to stack
 * Argument: input is the string containing the desired operation
 *  Note: requires top 2 datum to be both int datums or bool datums if input is 
 *        ==
 */
void RPNCalc::relationalOperatorCommand(const string& input)
{
    Datum top = stack.top();
    stack.pop();
    Datum deeper = stack.top();
    stack.pop();
    bool b = false;
    if (input == ">") 
        b = (deeper.getInt() > top.getInt());
    else if (input == "<")
        b = (deeper.getInt() < top.getInt());
    else if (input == "<=")
        b = (deeper.getInt() <= top.getInt());
    else if (input == ">=")
        b = (deeper.getInt() >= top.getInt());
    else if (input == "==")
        b = (deeper == top);
    stack.push(Datum(b));
}

/* isNumber
 * returns true if string contains a valid integer, false otherwise
 * Argument: str is the string containing data to be checked
 * Note: requires isdigit function from library
 */
bool RPNCalc::isNumber(const string& str)
{
    if (str == "-") // input is just a subtraction symbol, not an int
        return false;
    if (isdigit(str[0]) == 0 and str[0] != '-') // first char not int or -
        return false;
    for (size_t i = 1; i < str.length(); i++) { // loop thru
        if (isdigit(str[i]) == 0) return false; // if non digits, return false
    }
    return true; // all chars are numbers (exception: first char can be -)
}