/* 
 * File:   main.cpp
 * Author: John Huynh
 * Created on October 27, 2025
 * 
 * Purpose: Create a banking app using structures to record transactions
 */

// System Libraries
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Structures
struct Account {
    unsigned int accountNum; 
    int checkCount = 0, depositCount = 0;
    string name, address;
    float initBalance, balance;
    float *checks = nullptr, *deposits = nullptr;
};

// Prototypes
// float randomBalance();
float initBalance(const string &prompt);
string validateAccountDetails(const string &prompt);
unsigned int getAccountNumber(const string &prompt);
void clearInputBuffer();
void invalidInput();
void displayAccount(const Account &account);
void bankAccountMenu(Account &account);
void recordTransaction(Account &account, int action);   
void appendAmount(float *&arr, int &count, float amount);
void viewHistory(const Account &account);
float sumArray(const float *arr, int count);

// Main Execution
int main() {

    // Create Random Seed (set for random starting balance)
    srand(static_cast<unsigned int>(time(0)));

    // Create Account
    Account account;

    // Get Account Details
    account.accountNum = getAccountNumber("Enter 5 Digit Account Number: ");
    account.name = validateAccountDetails("Verify Account Holder's Name: ");
    account.address = validateAccountDetails("Verify Account Holder's Address: ");
    // account.initBalance = randomBalance();
    account.initBalance = initBalance("Current Balance of the Account: ");
    account.balance = account.initBalance;

    // Show what we captured
    displayAccount(account);
    bankAccountMenu(account);

    // Exit Stage Right
    delete [] account.checks;
    delete [] account.deposits;
    account.checks = nullptr;
    account.deposits = nullptr;
    account.checkCount = 0;
    account.depositCount = 0;

    return 0;

}

// Clear Leftovers
void clearInputBuffer() {

    cin.ignore(10000, '\n');

}

// Invalid Inputs
void invalidInput() {

    cin.clear();
    clearInputBuffer();
    cout << "Invalid input. Please try again.\n";

}

// Validate the Account Number
unsigned int getAccountNumber(const string &prompt) {

    unsigned int num;
    bool validID = false;

    do {
        cout << prompt;
        cin >> num;

        if (!cin.good()) {
            invalidInput();
            continue;
        } else if (num < 10000 || num > 99999) {
            cout << "Invalid entry. Account numbers are 5 digits\n";
        } else {
            validID = true;
        }

    } while (!validID);

    clearInputBuffer();
    return num;

}

// Validate Account Details - Name and Address
string validateAccountDetails(const string &prompt) {

    string input;
    bool valid = false;

    do {
        cout << prompt;
        getline(cin, input);

        if (!cin.good() || input.empty()) {
            invalidInput();
            continue;
        } else {
            valid = true;
        }

    } while (!valid);

    return input;
}

// Set an initial account balance
// float randomBalance() {
//     float balance = 100 + (rand() % 190001) / 100.0;
//     return balance;
// }

float initBalance(const string &prompt) {
    bool valid = false;
    float initBalance;

    do {
        cout << prompt;
        cin >> initBalance;

        if (!cin.good()) {
            invalidInput();
            continue;
        } else {
            valid = true;
        }

    } while (!valid);

    return initBalance;
}

// Display Account Info
void displayAccount(const Account &account) {

    cout << fixed << setprecision(2);
    cout << "\nHello " << account.name << ", here's your account dashboard\n\n";
    cout << setw(20) << left << "Account Number: " << account.accountNum << "\n";
    cout << setw(20) << left << "Address: " << account.address << "\n";
    cout << setw(20) << left << "Account Balance: " << "$" << account.balance << "\n";

}

// Bank Account Menu
void bankAccountMenu(Account &account) {

    int choice = 0;

    do {
        cout << "\nPlease choose an option below:\n";
        cout << "1. Record Checks\n";
        cout << "2. Record Deposits\n";
        cout << "3. View History\n";
        cout << "4. Logout\n";
        cout << "\nEnter your choice (1-4): ";
        cin >> choice;

        if (!cin.good()) {
            invalidInput();
            continue;
        }

        switch (choice) {
            case 1:
                cout << "\nRecord Checks selected.\n";
                recordTransaction(account, 1);
                displayAccount(account);
                break;
            case 2:
                cout << "\nRecord Deposits selected.\n";
                recordTransaction(account, 2);
                displayAccount(account);
                break;
            case 3:
                cout << "\nView History selected.\n";
                viewHistory(account);
                displayAccount(account);
                break;
            case 4:
                cout << "\nThank you banking with us " << account.name << "!" << endl;
                break;
            default:
                cout << "Invalid entry. Please try again.\n";
                break;

        }

    } while (choice != 4);

}

// Record Checks and Deposits
void recordTransaction(Account &account, int choice) {

    const float overdraftFee = 20.0;
    unsigned int action = 0;
    float amount = 0.0;

    do {

        cout << fixed << setprecision(2);
        cout << "\nCurrent Balance: $" << account.balance << '\n';
        cout << "\nEnter " << (choice == 2 ? "deposit" : "check") << " amount: $";
        cin >> amount;

        if (!cin.good()) { 
            invalidInput(); 
            continue; 
        }

        if (amount <= 0) { 
            cout << "Amount must be positive.\n"; 
            continue;
         }

        if (choice == 1) {

            // Deduct from Balance
            account.balance -= amount;
            bool overdrafted = false;

            // Determine if Overdrafted
            if (account.balance < 0) {
                overdrafted = true;
                account.balance -= overdraftFee;
            }
            
            appendAmount(account.checks, account.checkCount, amount);

            if (overdrafted) {
                cout << "\nThis check has overdrawn your account and a $20 overdraft fee has been applied.\n";
            }

            cout << "\nCheck for $" << amount << " recorded.\n";

        } else {

            // Deposit into Balance
            account.balance += amount;
            appendAmount(account.deposits, account.depositCount, amount);
            cout << "\nDeposit of $" << amount << " recorded.\n";
            
        }

        cout << "New Balance: $" << account.balance << "\n";

        // Mini menu
        cout << "\n1. Record another " << (choice == 2 ? "deposit" : "check") << '\n';
        cout << "2. Return to Menu\n";
        cout << "\nEnter choice (1-2): ";
        cin >> action;

        if (!cin.good()) { 
            invalidInput(); 
            action = 2; 
        }

    } while (action == 1);

}

// Add Check to Account
void appendAmount(float *&arr, int &count, float amount) {

    float *expanded = new float[count + 1];

    for (int i = 0; i < count; ++i) expanded[i] = arr ? arr[i] : 0.0;

    expanded[count] = amount;

    // Delete Existing Pointer
    delete [] arr;

    // Create New Pointer
    arr = expanded;

    // Update Count of Recorded Checks or Deposits
    ++count;

}

// Record Log
void viewHistory(const Account &account) {

    cout << fixed << setprecision(2);

    float totalChecks   = sumArray(account.checks, account.checkCount);
    float totalDeposits = sumArray(account.deposits, account.depositCount);

    cout << "\nTransaction History\n";
    cout << "Starting Balance : $" << account.initBalance << "\n\n";

    // Checks
    cout << "Check Count: " << account.checkCount << "\n\n";

    if (account.checkCount == 0) {

        cout << "No checks recorded.\n";

    } else {

        for (int i = 0; i < account.checkCount; ++i) {
            cout << (i+1) << ": $" << account.checks[i] << "\n";
        }

    }

    cout << "\nTotal Checks: $" << totalChecks << "\n\n";

    // Deposits
    cout << "Deposits:" << account.depositCount << "\n\n";

    if (account.depositCount == 0) {

        cout << "No deposits recorded.\n";

    } else {
        for (int i = 0; i < account.depositCount; ++i) {

            cout << (i+1) << ": $" << account.deposits[i] << "\n";

        }
    }

    cout << "\nTotal Deposits: $" << totalDeposits << "\n";

    float netChange = (account.balance - account.initBalance);
    cout << "\nNet Change: " << (netChange >= 0 ? "+" : "-") << "$" << (netChange >= 0 ? netChange : -netChange) << "\n";
    cout << "Current Balance : $" << account.balance << "\n";
    cout << "\nPress Enter to return to your dashboard...";

    clearInputBuffer();
    cin.get(); 

}

float sumArray(const float *arr, int count) {

    float sum = 0.0;
    for (int i = 0; i < count; ++i) sum += arr ? arr[i] : 0.0;
    return sum;

}