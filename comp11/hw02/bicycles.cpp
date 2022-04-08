// Harry Ahearn 2/19/21
//
// bicycles.cpp
//
// purpose: Takes in amount of parts from user and shows possible amount of 
// bikes that could be made from that combination of parts and outputs 
// remaining number of parts

#include <iostream>
using namespace std;

// constants for parts per bike
const int W_PER_BIKE = 2;
const int L_PER_BIKE = 50;
const int F_PER_BIKE = 1;

string plural(int n, string str);

int main() {
    // declaring ints, bFromF = bikes possible from frames, etc
    int numWheels, numLinks, numFrames, bFromW, bFromF, bFromL,
    totalBikesPossible;
    
    // declaring strings for output
    string wheelStr = "wheel";
    string frameStr = "frame";
    string linkStr = "link";
    string bikeStr = "bike";
    
    cout << "Enter the number of wheels: ";
    cin >> numWheels;
    
    // JFFE
    if(numWheels < 0) {
        cout << "Input must be positive. Enter the number of wheels: ";
        cin >> numWheels;
    }
    
    cout << "Enter the number of frames: ";
    cin >> numFrames;
    
    // JFFE
    if(numFrames < 0) {
        cout << "Input must be positive. Enter the number of frames: ";
        cin >> numFrames;
    }
    
    cout << "Enter the number of links: ";
    cin >> numLinks;
    
    // JFFE
    if(numLinks < 0) {
        cout << "Input must be positive. Enter the number of links: ";
        cin >> numLinks;
    }
    
    // compute possible amount of bikes from given inputs
    bFromW = numWheels / W_PER_BIKE;
    bFromF = numFrames / F_PER_BIKE;
    bFromL = numLinks / L_PER_BIKE;
    
    // compute total bikes possible based on above variables
    if(bFromW < bFromF && bFromW < bFromL) { // bFromW is smallest
        totalBikesPossible = bFromW;
    }
    else if(bFromF < bFromW && bFromF < bFromL) { // bFromF is smallest
        totalBikesPossible = bFromF;
    }
    else { // bFromL is smallest
        totalBikesPossible = bFromL;
    }
    
    // compute number of each part remaining after making bikes
    numWheels -= W_PER_BIKE * totalBikesPossible;
    numFrames -= F_PER_BIKE * totalBikesPossible;
    numLinks -= L_PER_BIKE * totalBikesPossible;
    
    bikeStr = plural(totalBikesPossible, bikeStr);
    wheelStr = plural(numWheels, wheelStr);
    frameStr = plural(numFrames, frameStr);
    linkStr = plural(numLinks, linkStr);
    
    // output
    cout << "You can make " << totalBikesPossible <<  " " << bikeStr << ". ";
    
    cout << "There are " << numWheels << " " << wheelStr << ", " << numFrames
    << " " << frameStr << ", " << numLinks << " " << linkStr << " leftover."
    << endl;
}

/**
 * plural
 * parameters: n - amount of object, str - string to be modified
 * purpose: add an s to a string if it has a plural amount
 * return: str
 */
string plural(int n, string str) {
    if(n != 1) {
        return str + "s";
    }
    return str;
}