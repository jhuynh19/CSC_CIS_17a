/* 
 * File:   gaddis_9_2_13_divSales.cpp
 * Author: John Huynh
 * Created on September 5th, 2025, 7:00 PM
 * Purpose:  Write a cout statement so the variable divSales is displayed in a field of 8 spaces, in fixed-point notation, with a precision of 2 decimal places. The decimal point should always be displayed.
 */

//System Libraries
#include <iostream> //I/O Library
#include <iomanip>  //I/O Manipulators Library
using namespace std;



// Main Function
int main() {
    float divSales;

    divSales = 7428;

    cout << setprecision(2) << fixed << showpoint << setw(8) << divSales;
    
    return 0;
}