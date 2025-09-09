/* 
 * File:   main.cpp
 * Author: John Huynh
 * Created on September 9th, 2025, 11:00 AM
 * Purpose:  Write a program that asks for the numerator and denominator of each fraction and displays the sum in fractional form.
 */

//System Libraries
#include <iostream> //I/O Library
#include <iomanip>  //I/O Manipulators Library

using namespace std;

// Main Function
int main() {

    // Variables
    int num1, num2, denom1, denom2; 
    float num_res, denom_res, result;
    char choice;

    cout << "Let's add fractions together \n\n";

    do {
        // Grab fractions from user
        cout << "Numerator of first fraction \t";
        cin >> num1;
        cout << "Denominator of first fraction \t";
        cin >> denom1;
        cout << "Numerator of second fraction \t";
        cin >> num2;
        cout << "Denominator of second fraction \t";
        cin >> denom2;
        
        // Calculate sum of two fractions [(ad + bc) / bd]
        num_res = (num1 * denom2) + (num2 * denom1);
        denom_res = denom1 * denom2;
        result = num_res / denom_res;
        
        // Output result
        cout << "\nResult as Fraction \t" << num_res << "/" << denom_res << endl;
        cout << "Result as Decimal \t" << setprecision(2) << fixed << showpoint << result << endl;

        // Add more fractions
        cout << "\nWant to add another fraction? (Y/N) \t";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');
    
    return 0;
}