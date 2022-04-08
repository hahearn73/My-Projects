/* Harry Ahearn 3/2/21
 * printlist.cpp  -- shows how to read a list of numbers into an array
 *
 *      1. read in data
 *      2. then prints out the list with line numbers using another loop
 *
 *   Exercises:
 *    [a] print the list in reverse
 *    [b] change loop to print out only the birthdays in October
 *    [c] after printing out the October bdays, print a count of how many
 *    [d] change to print the count for each month, not the actual bdays
 *    [e] use a function to do [c]
 *    [f] EXTRA: print which month has the MOST birthdays
 */
#include <iostream>

using namespace std;

const int CAPACITY = 1000;         // change as needed
void mostCommonMonth(int bdayCount[]);
void reverseOrder(int bdays[]);
void daysInMonth(int month, int bdays[]);
void bdaysInEachMonth(int bdays[]);

int main() 
{
        int bdays[CAPACITY];    // birthday data
        int used;               // number of spaces used so far
        int pos;                // position in array

        // read in CAPACITY values
        pos = 0;
        while (pos < CAPACITY) {
                cin >> bdays[pos];
                pos++;
        }
        used = pos;
        pos = 0;

        while (pos < used) {
                cout << pos << ". " << bdays[pos] << endl;
                ++pos;
        }
        
        reverseOrder(bdays); // a
        daysInMonth(1000, bdays); // b and c and e
        bdaysInEachMonth(bdays); // D and F
        
        return 0;        
}

/*
 * mostCommonMonth
 * parameters: array of bdays in each month
 * purpose: prints out most common month
 * void
 */
void mostCommonMonth(int bdayCount[]) {
    // prints out most common month and its amount of bdays F
    int mostCommonMonth = -1;
    int n = 0;
    for (int i = 0; i < 12; i++) {
        if (bdayCount[i] > n) {
            mostCommonMonth = i + 1;
            n = bdayCount[i];
        }
    }
    cout << "month with most bdays: " << mostCommonMonth << "\namount of bdays in most common month: " << n << endl;
}

/*
 * reverseOrder
 * parameters: all bdays
 * purpose: prints out all bdays in reverse order
 * void
 */
void reverseOrder(int bdays[]) {
    // reverse order A
    for(int pos = CAPACITY - 1; pos >= 0; pos--) {
        cout << pos << ". " << bdays[pos] << endl;
    }
}

/*
 * daysInMonth
 * parameters: the month and the list of bdays
 * purpose: prints out all bdays in that month and the total amount of them
 * void 
 */
void daysInMonth(int month, int bdays[]) {
    int sum = 0;
    for (int pos = 0; pos < CAPACITY; pos++) {
        if (bdays[pos] >= month && bdays[pos] < month + 100) {
            cout << bdays[pos] << endl;
            sum++;
        }
    }
    
    // prints num of bdays in october C
    cout << "num bdays in month " << month << ": " << sum << endl;
}

void bdaysInEachMonth(int bdays[]) {
    int bdayCount[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
    for (int i = 0; i < CAPACITY; i++) {
        if (bdays[i] < 200) bdayCount[0]++;
        else if (bdays[i] >= 200 && bdays[i] < 300) bdayCount[1]++;
        else if (bdays[i] >= 300 && bdays[i] < 400) bdayCount[2]++;
        else if (bdays[i] >= 400 && bdays[i] < 500) bdayCount[3]++;
        else if (bdays[i] >= 500 && bdays[i] < 600) bdayCount[4]++;
        else if (bdays[i] >= 600 && bdays[i] < 700) bdayCount[5]++;
        else if (bdays[i] >= 700 && bdays[i] < 800) bdayCount[6]++;
        else if (bdays[i] >= 800 && bdays[i] < 900) bdayCount[7]++;
        else if (bdays[i] >= 900 && bdays[i] < 1000) bdayCount[8]++;
        else if (bdays[i] >= 1000 && bdays[i] < 1100) bdayCount[9]++;
        else if (bdays[i] >= 1100 && bdays[i] < 1200) bdayCount[10]++;
        else if (bdays[i] >= 1200) bdayCount[11]++;
    }    
    cout << "bdays in each month: ";
    for (int i = 0; i < 12; i++) {
        cout << bdayCount[i] << " ";
    }    
    cout << endl;
    mostCommonMonth(bdayCount);
}
