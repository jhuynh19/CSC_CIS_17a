/* 
 * File: main.cpp
 * Author: John Huynh
 * Created on September 9th, 2025, 10:00 PM
 * Modified on October 21st, 2025
 * Purpose: Define an enumerated data type with enumerators for months(JANUARY, FEBRUARY, so on). 
 * The program should use the enumerated type to step through the elements of the array
 */

//System Libraries
#include <iostream>
#include <iomanip>
using namespace std;

enum Month { JANUARY, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER };

int main() {
    const int MAX_MONTHS = 6;
    float rain[MAX_MONTHS];
    int high[MAX_MONTHS];
    int low[MAX_MONTHS];
    int count = 0;

    // Input Month Data
    for (Month month = JANUARY; month < MAX_MONTHS; month = static_cast<Month>(month + 1)) {
        cout << "Enter the total rainfall for the month:\n";
        if (!(cin >> rain[month])) break;
        cout << "Enter the high temp:\n";
        if (!(cin >> high[month])) break;
        cout << "Enter the low temp:\n";
        if (!(cin >> low[month])) break;
        count++;
    }

    // Calculations
    float totalRain = 0;
    float totalAvgTemp = 0;
    int highest = high[0];
    int lowest = low[0];

    for (int i = 0; i < count; i++) {
        totalRain += rain[i];
        totalAvgTemp += (high[i] + low[i]) / 2.0;
        if (high[i] > highest) highest = high[i];
        if (low[i] < lowest) lowest = low[i];
    }

    float avgRain = totalRain / count;
    float avgTemp = totalAvgTemp / count;

    // Output
    cout << fixed << setprecision(2);
    cout << "Average monthly rainfall:" << avgRain << endl;
    cout << "High Temp:" << highest << endl;
    cout << "Low Temp:" << lowest << endl;
    cout << setprecision(1);
    cout << "Average Temp:" << avgTemp;

    return 0;
}