/* 
 * File:   main.cpp
 * Author: John Huynh
 * Created on October 29, 2025
 * 
 * Purpose: Create an encryption program for 4-digit integers
 */

// Libraries
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Prototypes
void invalidInput(const string &prompt);
bool validateInput(const string &num);
void clearInputBuffer();
void encryptNumber();
void decryptNumber();
void outputNum(const string &num, const string &prompt);

int main() {

    string num;
    int choice = 0;

    do {
        cout << "\nPlease choose an option below:\n";
        cout << "1. Record Checks\n";
        cout << "2. Record Deposits\n";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nRecord Checks selected.\n";
                encryptNumber();
                break;
            case 2:
                cout << "\nRecord Deposits selected.\n";
                decryptNumber();
                break;
            case 3:
                cout << "\nExit\n";
                break;
            default:
                invalidInput("Invalid input. Please try again.");
                break;
        }

    } while (!choice);
    
    return 0;
}

// Encrypt number
void encryptNumber() {

    string num;

     // Prompt
    cout << "Encrypt a four integer number. Integers must be between 0-7 ";
    cin >> num;

    // Validate Entry
    if (!validateInput(num)) return;

    // Replace each digit with sum of digit plus 3 modulus 8
    for (char &c : num) {
        int encrypDigit = (c - '0' + 3) % 8;
        c = char('0' + encrypDigit);
    }

    // Swap the 1st and 3rd, 2nd and 4th
    swap(num[0], num[2]);
    swap(num[1], num[3]);

    // Output Encrypted Number
    for (char &c : num) {
        int decrypDigit = (c - '0' + 3) % 8;
        c = char('0' + decrypDigit);
    }

    outputNum(num, "Your encrypted number: ");

}

void decryptNumber() {
    
    string num;

    // Prompt
    cout << "Decrypt a four integer number. Integers must be between 0-7 ";
    cin >> num;

    // Validate Entry
    if (!validateInput(num)) return;

    // Swap the 1st and 3rd, 2nd and 4th
    swap(num[0], num[2]);
    swap(num[1], num[3]);

    // Decrypt the provided number
    for (char &c : num) {
        int encrypDigit = (c - '0' + 5) % 8;
        c = char('0' + encrypDigit);
        cout << c;
    }
}

// Invalid Inputs
void invalidInput(const string &prompt) {
    cin.clear();
    clearInputBuffer();
    cout << prompt << "\n";
}

// Clear Leftovers
void clearInputBuffer() {
    cin.ignore(10000, '\n');
}

// Validate Entry
bool validateInput(const string &num) {
    // Check that input is exactly four characters
    if (num.size() != 4) {
        invalidInput("Not a four digit number.");
        return false;
    }

    // Check each character
    for (char c : num) {
        if (!isdigit(c)) {
            invalidInput("Input must contain only numbers.");
            return false;
        }

        if (c < '0' || c > '7') {
            invalidInput("Input must contain numbers between 0–7.");
            return false;
        }
    }

    // Passed all checks
    return true;
}

// Output Number
void outputNum(const string &num, const string &prompt) {
    cout << setw(25) << left << prompt << num << endl;
}