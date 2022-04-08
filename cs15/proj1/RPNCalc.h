/* Harry Ahearn 10/26/21 CalcYouLater RPNCalc.h
This is the interface for the RPNCalc class. This class is used to create a 
calculator that reads in reverse polish notation as well as some more complex 
commands using a stack as the storage for the calculator. The default 
constructor and destructor are defined in this file and empty as there is 
nothing that they can do as the DatumStack stack is really a vector of type 
Datum. The only public function is run which is a command loop that can passes 
input to the wrapper functions which then call the actual functions that the 
calculator can perform. All such functions are private as they should not be 
called by anything outside the class.
*/

#ifndef _RNPCALC_H_
#define _RNPCALC_H_
#include "DatumStack.h"
#include "Datum.h"

class RPNCalc {
public:
    RPNCalc(){};
    ~RPNCalc(){};
    void run(); // command loop
    
private:
    DatumStack stack; // stack containing Datum to be stored by class
    
    // wrapper functions
    bool simpleCommand(const std::string& input, std::istream& stream);
    void complexCommands(const std::string& input, std::istream& stream);
    
    // simple commands
    void mathOperatorCommand(const std::string& input);
    void relationalOperatorCommand(const std::string& input);
    void boolCommand(const std::string& input);
    void swapCommand();
    void notCommand();
    
    // complex commands
    void RStringCommand(std::istream& stream);
    void execCommand();
    void fileCommand();
    void ifCommand();
    
    // helper function
    bool isNumber(const std::string& str); // tests if input is an int
};
#endif