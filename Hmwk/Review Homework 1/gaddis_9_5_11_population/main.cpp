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
    int numOrgs, days, total, i;
    float grwthPcnt;
    char choice;

    numOrgs = 2;

    cout << "Let's grow a population! \n\n";

    do {
        // Take user's input
        do {
            if(numOrgs < 2) { // User must provide at least 2 organisms
                cout << "\nYou must have at least two organisms to reproduce!\n";
            }
            cout << "How many organisms are you starting with?\t";
            cin >> numOrgs;
        } while (numOrgs < 2);

        do {
            if(grwthPcnt < 0) { // User must provide at least 2 organisms
                cout << "\nYou must provide a growth factor!\n";
            }
            cout << "\nHow fast does it multiply? (%)\t";
            cin >> grwthPcnt;
        } while (grwthPcnt < 0);
        
        do {
            if(days < 0) { // User must provide at least 2 organisms
                cout << "\nYou must give at least a day for it to reproduce!\n";
            }
            cout << "\nHow many days will it be allowed to grow?\t";
            cin >> days;
        } while (days < 0);
            
        // Calculations
        i = 0;
        total = numOrgs;

        while(i < days) {
            total = total * (1 + (grwthPcnt/100));
            i++;
        }
        
        // Output result
        cout << "\nYou'll have " << total << " organisms at the end of " << days << " days" << endl;

        // Run again
        cout << "\nWant to grow another organism? (Y/N) \t";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');
    
    return 0;
}