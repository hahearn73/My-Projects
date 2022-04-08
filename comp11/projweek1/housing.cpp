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
        (void) argc;
        
        House all_houses[ROWS][COLS];
        fill_with_no_houses(ROWS, COLS, all_houses);
        if(!read_all_house_data(argv[1], all_houses))
                return 1; // ends program if file could not be opened
        
        int row, col;
        while(true) {
                cout << "Enter row: "; // getting row
                cin >> row;
                if (row < 0) // make sure row is valid
                        break;
                
                cout << "Enter col: "; // getting col
                cin >> col;
                if (col < 0) // make sure col is valid
                        break;
                
                print_house(all_houses[row][col]); // output result
        }

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
                all_houses[row_from_lot(h.lot_code)][col_from_lot(h.lot_code)]
                = h;
        } // fill array with each line in file
        
        inputFile.close(); // close ifstream
        return true;
}
