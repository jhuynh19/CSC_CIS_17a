/* 
 * File: main.cpp
 * Author: John Huynh
 * Created on September 9th, 2025, 12:20 PM
 * Purpose: Write a program that asks the user to enter the month (letting the user enter an integer in the range of 1 through 12) and the year. The program should then display the number of days in that month.
 */

//System Libraries
#include <iostream> //I/O Library

using namespace std;

// Main Function
int main() {

    // Variables
    int month, days, year;
    char choice;

    cout << "See how many days are in a specific month \n\n";

    do {
        // Take user's input
        cout << "Enter a month (1-12)\t";
        cin >> month;
        cout << "Enter a year\t";
        cin >> year;
            
        // Determine days in month
        switch(month) {

            // These months have 31 days
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                days = 31;
                break;

            // These months have 30 days
            case 4: case 6: case 9: case 11:
                days = 30;
                break;

            // February is special
            case 2:
                if ((year % 100 == 0 && year % 400 == 0) || (year % 100 != 0 && year % 4 == 0)) {
                    days = 29;
                } else {
                    days = 28;
                }
                break;

            default:
                cout << "Enter a valid month" << endl;
                return 1;
        }
        
        // Output result
        cout << "\n" << days << " days" << endl;

        // Run again
        cout << "\nWant to try another month? (Y/N) \t";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');
    
    return 0;
}