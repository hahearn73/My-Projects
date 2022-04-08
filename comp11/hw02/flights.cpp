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
 const int hoursInDay = 24 * 60;
 
 int main() {
     
     // Dep = departure, f1 = flight 1, Arr = arrival
     int f1DepHour, f1DepMin, f1ArrHour, f1ArrMin; 
     int f2DepHour, f2DepMin, f2ArrHour, f2ArrMin;
     
     cout << "Flight 1: ";
     cin >> f1DepHour;
     cin >> f1DepMin;
     cin >> f1ArrHour;
     cin >> f1ArrMin;
     
     cout << "Flight 2: ";
     cin >> f2DepHour;
     cin >> f2DepMin;
     cin >> f2ArrHour;
     cin >> f2ArrMin;
     
     // convert all times to minutes
     int f1Dep = convertToMins(f1DepHour, f1DepMin);
     int f1Arr = convertToMins(f1ArrHour, f1ArrMin);
     int f2Dep = convertToMins(f2DepHour, f2DepMin);
     int f2Arr = convertToMins(f2ArrHour, f2ArrMin);
     
     // overnight travel
     
     if (f1Arr < f1Dep) { // First flight arrives the following morning
         f1Arr += hoursInDay;
         f2Dep += hoursInDay;
         f2Arr += hoursInDay;
     }
     
     if (f1Arr > f2Dep) { // Second flight leaves the following morning
         f2Dep += hoursInDay;
         f2Arr += hoursInDay;
     }
     
     if (f2Dep > f2Arr) { // Second flight arrives the following morning
         f2Arr += hoursInDay;
     }
     
     // calculate layover
     int layover = f2Dep - f1Arr;
     int layoverHr = layover / 60;
     int layoverMin = layover % 60;
     
     // calculate total
     int total = f2Arr - f1Dep;
     int totalHr = total / 60;
     int totalMin = total % 60;
     
     // output 
     cout << "Layover: " << layoverHr << " hr " << layoverMin << " min" << endl;
     cout << "Total: " << totalHr << " hr " << totalMin << " min" << endl;
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
 