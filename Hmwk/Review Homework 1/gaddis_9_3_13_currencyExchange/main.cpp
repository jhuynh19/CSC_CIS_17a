/* 
 * File: main.cpp
 * Author: John Huynh
 * Created on September 9th, 2025, 12:00 PM
 * Purpose: Write a program that will convert U.S. dollar amounts to Japanese yen and to euros, storing the conversion factors in the constants YEN_PER_DOLLAR and EUROS_PER_DOLLAR. 
 */

//System Libraries
#include <iostream> //I/O Library
#include <iomanip>  //I/O Manipulators Library

using namespace std;

const float YEN_PER_DOLLAR = 147.41;
const float EUROS_PER_DOLLAR = 0.85;

// Main Function
int main() {

    // Variables
    float dollar, yen, euro;
    char choice;


    do {
        // Take user's USD input
        cout << "U.S Dollar Amount \t";
        cin >> dollar;
            
        // Convert currencies
        yen = dollar * YEN_PER_DOLLAR;
        euro = dollar * EUROS_PER_DOLLAR;
        
        // Output result
        cout << dollar << " USD equals " << yen << " Japanese Yen and " << euro << " Euro" << endl; 

        // Add more fractions
        cout << "\nWant to convert more USD? (Y/N) \t";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');
    
    return 0;
}