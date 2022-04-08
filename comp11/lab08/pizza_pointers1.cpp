/* Harry Ahearn
 * An exercise is using pointers and ordering pizza
 *
 * Mark A. Sheldon, Tufts University, Spring 2021
 */

#include <iostream>
#include <string>

using namespace std;

const int MAX_TOPPINGS = 2;

struct Pizza {
        bool   hasThinCrust;
        string toppings[MAX_TOPPINGS];
};

void printPizza(Pizza *pizza);
Pizza takeOrder();

int main()
{
        // PART a
        // You need to complete both functions below
        // to make this part work
        Pizza pie = takeOrder();

        cout << endl << "You ordered:  ";
        printPizza(&pie);
        cout << endl;

        // GET EVERYTHING WORKING UP TO HERE FIRST
        // THEN UNCOMMENT NEXT SECTION
        
        // PART b
        string *topping1Ptr = &pie.toppings[0];
        string *topping2Ptr = &pie.toppings[1];
        
        cout << "First topping is "  << *topping1Ptr << ", " << "Second topping is " << *topping2Ptr << endl;

        cout << "The toppings are stored at " << topping1Ptr << " and " << topping2Ptr << ", respectively" << endl << endl;


        // PART c
        
        *topping2Ptr = "cranberries";
        
        cout << "Now the pie has " << *topping2Ptr << endl;
        printPizza(&pie);
        cout << "See!" << endl;

        return 0;
}

void printPizza(Pizza *pizza)
{
        string crust;

        if ((*pizza).hasThinCrust)
                crust = "thin";
        else
                crust = "thick";

        cout << "A " << crust << " crust pizza with:  "
             << (*pizza).toppings[0]
             << " and "
             << (*pizza).toppings[1] << endl;
}

Pizza takeOrder()
{
        Pizza  order;
        string desiredCrust;
        
        cout << "Hello, I'll be your server today." << endl
             << "What kind of crust would you like, thick or thin?  ";
        cin  >> desiredCrust;
        if (desiredCrust == "thin") {
                order.hasThinCrust = true;
        } else if (desiredCrust == "thick") {
                order.hasThinCrust = false;
        } else {
                cout << "Right, thin it is!" << endl;
                order.hasThinCrust = true;
        }
        cout << "Please list exactly two toppings:  ";
        cin >> order.toppings[0];
        cin >> order.toppings[1];
      
        return order;
}
