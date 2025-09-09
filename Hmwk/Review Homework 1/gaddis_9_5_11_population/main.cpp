/* 
 * File: main.cpp
 * Author: John Huynh
 * Created on September 9th, 2025, 12:45 PM
 * Purpose: Write a program that will predict the size of a population of organisms. The program should ask the user for the starting number of organisms, their average daily population increase (as a percentage), and the number of days they will multiply. A loop should display the size of the population for each day
 * Note: Input Validation: Do not accept a number less than 2 for the starting size of the population. Do not accept a negative number for average daily population increase. Do not accept a number less than 1 for the number of days they will multiply.
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