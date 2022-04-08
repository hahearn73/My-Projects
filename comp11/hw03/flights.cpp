/* Harry Ahearn 2/19/21
 * 
 * flights.cpp
 *
 * purpose: take 2 flights as input, tell layover time and total travel time
 *
 */
 
 #include <iostream>
 using namespace std;
 
 int convertToMins(int hour, int min);
 int difference(int a, int b);
 void printMinsToHours(int n);
 const int minsInDay = 24 * 60;
 
 int main() {     
     int f1DepHour, f1DepMin, f1ArrHour, f1ArrMin;
     int f2DepHour, f2DepMin, f2ArrHour, f2ArrMin; 
     
     cout << "Flight 1: "; // flight 1 input 
     cin >> f1DepHour;
     cin >> f1DepMin;
     cin >> f1ArrHour;
     cin >> f1ArrMin;
     cout << "Flight 2: "; // flight 2 input
     cin >> f2DepHour;
     cin >> f2DepMin;
     cin >> f2ArrHour;
     cin >> f2ArrMin;
     
     // convert all times to minutes
     int f1Dep = convertToMins(f1DepHour, f1DepMin);
     int f1Arr = convertToMins(f1ArrHour, f1ArrMin);
     int f2Dep = convertToMins(f2DepHour, f2DepMin);
     int f2Arr = convertToMins(f2ArrHour, f2ArrMin);
     
     // calculates times
     int total = difference(f1Dep, f1Arr) + difference(f1Arr, f2Dep) + 
     difference(f2Dep, f2Arr); // calculates total
     int layover = difference(f1Arr, f2Dep); // calculates layover time
          
     // output 
     cout << "Layover: "; printMinsToHours(layover); // outputs layover time
     cout << "Total: "; printMinsToHours(total); // outputs total time
     return 0;
 }
 
 /*
  * convertToMins
  * parameters: time in hours and mins
  * purpose: converts time to total minutes
  * return amount of minutes
  */
 int convertToMins(int hour, int min) {
     return hour * 60 + min;
 }
 
 /*
  * difference
  * parameters: the two times
  * purpose: finds the difference between 2 times even if they are on different
  *          days
  * return: returns the difference between 2 times
  */
 int difference(int a, int b) {
     if(b < a) { // accounts for overnight travel
         b += minsInDay;
     }
     return (b - a);
 }
 
 /*
  * printsMinsToHours
  * parameters: a time in minutes
  * purpose: prints that time in hours and minutes
  * void no return
  */
 void printMinsToHours(int n) {
     cout << n / 60 << " hr " << n % 60 << " min" << endl;
 }
 