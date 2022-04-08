/* Harry Ahearn 10/26/21 CalcYouLater main.cpp
This is the driver file for the CalcYouLater program. It includes just a main 
function which creates an RPNCalc object and calls run on that object and 
returns 0 when finished.
*/

#include "RPNCalc.h"

/* main
 * driver function for the CalcYouLater program. Creates and RPNCalc object
 * and calls run on that object.
 */
int main() {
    RPNCalc r;
    r.run();
    return 0;
}