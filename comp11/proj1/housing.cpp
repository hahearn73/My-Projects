//===============================================================
//
//
//                        housing.cpp version
//                     Author: Harry Ahearn 
//                      Date: 3/22/21
//
// purpose: output details of houses given from a file
//
//===============================================================


#include <iostream>
#include <fstream>

using namespace std;

// DO NOT CHANGE THE FOLLOWING CONSTANTS. WHEN YOU SUBMIT,
// THEY MUST HAVE THESE VALUES AND THEY MUST BE USED 
// AS THE DIMENSIONS FOR YOUR all_houses ARRAY.
const int ROWS = 50;
const int COLS = 20;

//===============================================================
//
//                             House
//
//     Each House struct records the information about one
//     house.  Three of the fields are declared for you and
//     you MUST use them as given.  You should declare below
//     them any additional members that you need.
//
//     Note that if the "no_house_here" member field is set
//     to true, then the other fields are not used.  Of course,
//     if no_house_here is false; then all the fields should
//     be set.
//
//===============================================================

struct House {
        // ===================================================
        //    YOU MUST LEAVE THE DECLARATIONS FOR THESE FIELDS
        //    AS THEY ARE AND MUST USE THEM FOR THEIR STATED
        //    PURPOISE
        // ===================================================

        bool   no_house_here;  // true if there is NO house on this location
        int    id;             // id from the data file, converted to int
        string lot_code;       // lot_code string from the data file

        string color;          // color of house 
        float price;           // price of house 
        int bedrooms;          // number of bedrooms
        string avail;          // is available

};


//===============================================================
//                   REQUIRED FUNCTION PROTOTYPES
//
// Declare your other function prototypes here, but DO NOT 
// MODIFY ANY OF THE PROTOTYPES SUPPLIED FOR YOU BELOW!
// Note that these cannot be much higher up in your .cpp file because
// most of them need the declaration of struct House
//===============================================================

// - -  - - - - - - - - - - - - -  - - - - - - - - - - - 
//   Functions operating on a single house
// - -  - - - - - - - - - - - - -  - - - - - - - - - - - 

// read one line of the input_file; return corresponding House
House read_one_house(ifstream& input_file);

// print information about a single house
void print_house(House h);


// - -  - - - - - - - - - - - - -  - - - - - - - - - - - 
//   Functions relating to the array of houses
// - -  - - - - - - - - - - - - -  - - - - - - - - - - - 

// given a lot code, compute the column and row (respectively)
// in the all_houses array
int
col_from_lot(string lot);

int
row_from_lot(string lot);

//  set the no_house_here marker for every position
//  in the array
void
fill_with_no_houses(int rows, int cols, House all_houses[ROWS][COLS]);

//  given a file with a count n at the top
//  read the count and then n lines of house data
//  into appropriate positions in the array
//
//   return true if file was successfully read
//          false if file could not be opened
bool
read_all_house_data(string filename, House all_houses[ROWS][COLS]);

// returns true if house is available false otherwise, calls output func
bool
is_available(int id, House all_houses[ROWS][COLS]);

// prints output for is_available
void 
is_available_output(bool isAvail, int id);

// do while loop which continually asks for input and calls other functions
void
run_command_loop(House all_houses[ROWS][COLS]);

// finds amount of houses that meet specified criteria, calls output func
int 
matching_houses(float max_price, string desired_color, int desired_bedrooms, 
        House all_houses[ROWS][COLS], House results[ROWS * COLS]); 

// prints out houses that fit criteria        
void 
matching_houses_output(int n, House results[ROWS * COLS]);

// returns number of neighbors from a given house id, calls output func
int 
num_neighbors(int id, House all_houses[ROWS][COLS]);

// prints out number of neighbors
void 
num_neighbors_output(int n);

// sees if house is available/exists, sets it to booked if possible, calls 
// output func
int 
rent_house(int id, House all_houses[ROWS][COLS]);

// outputs result of rent_house
void
rent_house_output(int n);

// returns 1 if neighbor exists at position, 0 otherwise
int 
neighborExistsAt(int row, int col, House all_houses[ROWS][COLS]);

// ============================================================
//     INCLUDE COMP11 TESTING CODE
//
//   LEAVE THIS STATEMENT IN PLACE. IT MUST COME 
//   AFTER YOUR PROTOTYPE FUNCTION DECLARATIONS.
// ============================================================

#include "housing_hooks.hpp"

//======================================================================
//                      END FIXED STARTER CODE
//======================================================================

//======================================================================
//======================================================================
//
//            FOLLOWING THE INSTRUCTIONS PROVIDED FOR THIS 
//            PROJECT, FILL IN THE CODE FOR THE FUNCTIONS BELOW.
//
//======================================================================
//======================================================================


//======================================================================
//                              main 
//======================================================================

int
main(int argc, char *argv[])
{
        (void)argc;
        string filename = argv[1]; // get filename

        House all_houses[ROWS][COLS];
        fill_with_no_houses(ROWS, COLS, all_houses); // setup all_houses array

        if(!read_all_house_data(filename, all_houses)) { // if file couldnt open
                cerr << "housing.cpp: could not open file: " << filename << endl; // error message
                return 1; 
        }

        run_command_loop(all_houses); // run command loop

        return 0;
}

//======================================================================
//                       YOUR FUNCTIONS HERE
//
//        We give you empty starter code for some of the required
//        functions, but you should add any you need to make your
//        code well organized (if you feel the need!)
//======================================================================


// - -  - - - - - - - - - - - - -  - - - - - - - - - - - 
//   Functions operating on a single house
// - -  - - - - - - - - - - - - -  - - - - - - - - - - - 

// read one line of the input_file; return corresponding House
House read_one_house(ifstream& input_file) {
        House h;
        input_file >> h.id;
        input_file >> h.lot_code;
        input_file >> h.price;
        input_file >> h.bedrooms;
        input_file >> h.color;
        input_file >> h.avail;
        return h;
}

// print information about a single house
void print_house(House h)  {  
        // determine if house is available
        string availableStr = "No";
        bool available = (h.avail == "available");
        if (available)
                availableStr = "Yes";
                
        if (!h.no_house_here) // make sure house exists
                cout << "Id: " << h.id << " Lot: " << h.lot_code << " Color: " 
                << h.color << " Price: " << h.price << " Bedrooms: " << 
                h.bedrooms << " Available: " << availableStr << endl;
        else 
                cout << "No house" << endl;
}

// - -  - - - - - - - - - - - - -  - - - - - - - - - - - 
//   Functions relating to the array of houses
// - -  - - - - - - - - - - - - -  - - - - - - - - - - - 

// given a lot code, compute the column and row (respectively)
// in the all_houses array
int
col_from_lot(string lot) {
        return (lot[0] - 65);
}

int
row_from_lot(string lot) {
        // code from hw05 string_to_int
        int n = 0; // int of digits in string s
        for (size_t i = 1; i < lot.length(); i++) {
            if (lot[i] >= 48 && lot[i] <= 57) { // if character is digit
                n = n * 10 + lot[i] - 48; // puts digit at end of return integer
            }
        }  
        return n - 1; // subtract 1 because arrays start at 0
}

//  set the no_house_here marker for every position
//  in the array
void
fill_with_no_houses(int rows, int cols, House all_houses[ROWS][COLS]) {        
        for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                        all_houses[i][j].no_house_here = true;
                }
        }
}

//  given a file with a count n at the top
//  read the count and then n lines of house data
//  into appropriate positions in the array
//
//   return true if file was successfully read
//          false if file could not be opened
bool
read_all_house_data(string filename, House all_houses[ROWS][COLS]) {
        // open ifstream
        ifstream inputFile;
        inputFile.open(filename);
        if (not inputFile.is_open()) {
                cerr << "fileread.cpp: could not open file: " << filename << 
                endl;
                return false;
        }
        
        int n;
        inputFile >> n; // length of file integer
        
        for (int i = 0; i < n; i++) {
                House h = read_one_house(inputFile);
                h.no_house_here = false;
                all_houses[row_from_lot(h.lot_code)][col_from_lot(h.lot_code)]
                = h;
        } // fill array with each line in file
        
        inputFile.close(); // close ifstream
        return true;
}

/*
 * purpose:   determines if a given house is available based on its ID
 * args:      id of house, array of houses 
 * returns:   true if available, false otherwise
 * notes:     returns false if house doesnt exist; calls output func
 */
bool is_available(int id, House all_houses[ROWS][COLS]) {
        bool isAvail = false;
        
        for (int i = 0; i < ROWS; i++) { // search for house with matching id
                for (int j = 0; j < COLS; j++) {
                        if (all_houses[i][j].id == id && all_houses[i][j].avail == "available") // is it a match and available
                                isAvail = true;
                }
        }
        
        is_available_output(isAvail, id); // output
        return isAvail; // return statement
}

/*
 * purpose:   outputs result of is_available
 * args:      boolean that contains if house is available, house id #
 * void 
 * notes:     called by is_available
 */
void is_available_output(bool isAvail, int id) {
        if(!isAvail) // output if not found
                cout << "Sorry, House " << id << " is not available" << endl;
        else // output if found
                cout << "House " << id << " is available" << endl;
}

/*
 * purpose:   finds amount of houses that match given criteria
 * args:      criteria to be met: price, color, bedroom #, house array, results
 * returns:   amount of houses that match given criteria
 * notes:     changes arrays despite not returning them; calls output func
 */
int matching_houses(float max_price, string desired_color, int desired_bedrooms, House all_houses[ROWS][COLS], House results[ROWS * COLS]) {
        int n = 0;
        
        for (int i = 0; i < ROWS; i++) { // loop thru array
                for (int j = 0; j < COLS; j++) { // look for a match
                        if (all_houses[i][j].price <= max_price && all_houses[i][j].color == desired_color && all_houses[i][j].bedrooms >= desired_bedrooms) {
                                results[n] = all_houses[i][j];
                                n++; // if found, add 1 to n
                        }
                }
        }
        
        matching_houses_output(n, results); // print output
        return n;
}

/*
 * purpose:    prints houses that match criteria as specified by matching_houses
 * args:       amount of houses, array of matching houses 
 * void 
 * notes:      called by matching_houses
 */
void matching_houses_output(int n, House results[ROWS * COLS]) {
        for (int i = 0; i < n; i++) {
                print_house(results[i]);
        }
}

/*
 * purpose:   finds the number of neighbors around a given house
 * args:      house id number and house array 
 * returns:   neighbor count 
 * notes:     calls output func
 */
int num_neighbors(int id, House all_houses[ROWS][COLS]) {
        House h;
        bool exists = false;
        int row, col;
        for (int i = 0; i < ROWS; i++) { // search for house with matching id
                for (int j = 0; j < COLS; j++) {
                        if (all_houses[i][j].id == id) { // is it a match and available
                                h = all_houses[i][j];
                                exists = true;
                                row = row_from_lot(h.lot_code);
                                col = col_from_lot(h.lot_code);
                        }
                }
        }
        
        int n = 0;
        if (exists) { // if house exists, search for it in a 3x3 square around it except its own space
                n += neighborExistsAt(row - 1, col - 1, all_houses);
                n += neighborExistsAt(row - 1, col, all_houses);
                n += neighborExistsAt(row - 1, col + 1, all_houses);
                n += neighborExistsAt(row, col - 1, all_houses);
                n += neighborExistsAt(row, col + 1, all_houses);
                n += neighborExistsAt(row + 1, col - 1, all_houses);
                n += neighborExistsAt(row + 1, col, all_houses);
                n += neighborExistsAt(row + 1, col + 1, all_houses);
        }
        
        num_neighbors_output(n); // output function
        return n;
}

/*
 * purpose:   says if a neighbor is in range and exists 
 * args:      positive of neighbor, array 
 * returns:   1 if found, 0 if not found 
 * notes:     returns 0 if position is out of bounds
 */
int neighborExistsAt(int row, int col, House all_houses[ROWS][COLS]) {
        if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
                if (!all_houses[row][col].no_house_here)
                        return 1;
        }
        return 0;
}

/*
 * purpose:   outputs amount of neighbors specified by num_neighbors
 * args:      amount of neighbors 
 * void 
 * notes:     called by num_neighbors
 */
void num_neighbors_output(int n) {
        cout << "You have " << n << " neighbors!" << endl; 
}

/*
 * purpose:   if house is available, it will say it is unavailable, calls output
 * args:      house id #, houses array 
 * returns:   0 if house doesn't exist, 1 if successful, 2 if house is booked
 * notes:     calls output func, edits all_houses array
 */
int rent_house(int id, House all_houses[ROWS][COLS]) {
        bool exists = false;
        House house;
        
        for (int i = 0; i < ROWS; i++) { // search for house with matching id
                for (int j = 0; j < COLS; j++) {
                        if (all_houses[i][j].id == id && id > 0) {
                                house = all_houses[i][j]; // store that house
                                exists = true; 
                        }
                }
        }
        
        if (exists) {  // if exists 
                if (house.avail != "booked") { // rent it
                        all_houses[row_from_lot(house.lot_code)][col_from_lot(house.lot_code)].avail = "booked"; // change avail
                        rent_house_output(0); // output
                        return 1;
                }
                else { // exists but booked
                        rent_house_output(1); // output
                        return 2;
                }
        }
        rent_house_output(2); // output for does not exist
        return 0;
}

/*
 * purpose:   outputs result of rent_house
 * args:      0 if success, 1 if failed, 2 if non existant
 * void 
 * notes:     called by rent_house
 */
void rent_house_output (int n) {
        if (n == 0) // house rented successfully 
                cout << "Congrats, you rented a house! Hope your door knobs don't fall off" << endl;
        else if (n == 1) // house is already rented
                cout << "Too late...i hear the dumpster behind hill has some spaces open" << endl;
        else  // no house exists there
                cout << "You can't rent a house that doesn't exist, but good try" << endl;
}

/*
 * purpose:   loops a query to user which then invokes other functions 
 * args:      the houses array 
 * void 
 * notes:     is called by main function directly
 */
void run_command_loop(House all_houses[ROWS][COLS]) {
        string action, desired_color; // variables needed for loop
        int id, desired_bedrooms;
        float max_price;
        
        do { // what is being looped thru
                cout << "query-> "; 
                cin  >> action; 

                if (action == "a") { // is_available
                        cin >> id;
                        is_available(id, all_houses); 
                } 
                else if (action == "m") { // matching_houses
                        cin >> max_price;
                        cin >> desired_color;
                        cin >> desired_bedrooms;
                        House results[ROWS * COLS];
                        matching_houses(max_price, desired_color, desired_bedrooms, all_houses, results);
                }
                else if (action == "n") { // num_neighbors
                        cin >> id;
                        num_neighbors(id, all_houses);
                }
                else if (action == "r") { // rent_house
                        cin >> id;
                        rent_house(id, all_houses);
                }
        } while (action != "q"); // stops if q is input
}
