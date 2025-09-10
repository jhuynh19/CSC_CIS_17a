/* 
 * File: main.cpp
 * Author: John Huynh
 * Created on September 9th, 2025, 10:00 PM
 * Purpose: Write a function named calculateWeight that accepts the name of the planet and an object’s weight on Earth as arguments, and returns the weight on that planet.
 * Demonstrate the function by calling it in a program that asks the user to enter values for the planet and the weight.
 */

//System Libraries
#include <iostream>
#include <iomanip>

using namespace std;

// Prototypes
void calculateWeight(int plntChc, float hmWght);

// Main Function
int main() {

    // Variables
    int plntChc; // Planet Choice
    double hmWght, cnvtWght; // Weight on Earth / Converted Weight
    char choice;

    cout << "Let's see how much an object weighs on a specific planet! \n\n";

    do {
        // List planets to choose from
        cout << "Choose a planet:\n";
        cout << "1. Mercury\n";
        cout << "2. Venus\n";
        cout << "3. Mars\n";
        cout << "4. Jupiter\n";
        cout << "5. Saturn\n";
        cout << "6. Uranus\n";
        cout << "7. Neptune\n";
        cout << "\nEnter your choice (1-7):\t";
        cin >> plntChc;

        // Get weight
        cout << "\nEnter the object's weight on Earth (lbs):\t";
        cin >> hmWght;

        // Supply calculateWeight() function with planet choice and weight
        calculateWeight(plntChc, hmWght);

        // Run again
        cout << "\nWant to weigh another object? (Y/N) \t";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');
    
    return 0;
}

void calculateWeight(int plntChc, float hmWght) {

    // Planet Names
    string planets[] = {"Mercury", "Venus", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"};

    // Gravity value of planet
    float gravity[] = {
        0.38, // Mercury
        0.91, // Venus
        0.38, // Mars
        2.34, // Jupiter
        1.06, // Saturn
        0.92, // Uranus
        1.19  // Neptune
    };

    if (plntChc >= 1 && plntChc <= 7) {
        double newWeight = hmWght * gravity[plntChc - 1];
        cout << "On " << planets[plntChc - 1] << ", the object would weigh " << fixed << setprecision(2) << newWeight << " lbs.\n";
    } else {
        cout << "\nInvalid planet choice!\n";
    }
}