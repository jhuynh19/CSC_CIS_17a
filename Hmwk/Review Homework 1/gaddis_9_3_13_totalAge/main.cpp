/* 
 * File:   main.cpp
 * Author: John Huynh
 * Created on September 8th, 2025, 5:00 PM
 * Purpose:  Write a cout statement so the variable totalAge is displayed in a field of 12 spaces, in fixed-point notation, with a precision of 4 decimal places.
 */

//System Libraries
#include <iostream> //I/O Library
#include <iomanip>  //I/O Manipulators Library
using namespace std;

// Main Function
int main() {
    float totalAge;

    totalAge = 35.3328213197;

    cout << setprecision(4) << fixed << showpoint << setw(12) << totalAge;
    
    return 0;
}