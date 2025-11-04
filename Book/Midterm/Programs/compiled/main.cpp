/* 
 * File:   main.cpp
 * Author: John Huynh
 * Created on October 31, 2025
 * 
 * Purpose: Compiled Menu Program for Midterm
 */

// System Libraries
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

// Structures
struct Account {
    unsigned int accountNum; 
    int checkCount = 0, depositCount = 0;
    string name, address;
    float initBalance, balance;
    float *checks = nullptr, *deposits = nullptr;
};
struct Company {
    string name, address, city, state, zip;
};
struct Employee {
    string name;
    float hours, rate, gross;
};
struct Prime {
    unsigned char power;
    unsigned short prime;
};
struct Primes {
    unsigned short n;
    unsigned char nPrimes;
    Prime* pStrAry;
};

// Structure Prototypes
Company* createCompanies(int &companyCount);
Primes* factor(int num);

// Boolean Prototypes
bool isPrime(int);
bool validateInput(const string &num);
bool validatePrimeInput(int &num);

// Float Prototypes
float computeGross(float hours, float rate);
float initBalance(const string &prompt);
float sumArray(const float *arr, int count);

// Int Prototypes
int power(int, int &);
int nPrimes(int);
unsigned int getAccountNumber(const string &prompt);

// String Prototypes
string chunkToText(int n);
string getAmountInWords(float amount);
string validateAccountDetails(const string &prompt);

// Voided Programs
void program_1();
void program_2();
void program_3();
void program_4();
void program_5();
void program_6();
void program_7();

// The Voided Prototypes
void clearInputBuffer();
void invalidInput(const string &prompt);
void createEmployees(Company* companies, int companyCount, Employee** &roster, int* &employeeCount);
void deleteCompanyData(Company* companies, Employee** roster, int* employeeCount, int companyCount);
void generateChecks(Company* companies, Employee** roster, int* employeeCount, int companyCount);
void displayAccount(const Account &account);
void bankAccountMenu(Account &account);
void recordTransaction(Account &account, int action);   
void appendAmount(float *&arr, int &count, float amount);
void viewHistory(const Account &account);
void encryptNumber();
void decryptNumber();
void outputNum(const string &num, const string &prompt);
void test_integer(const char* label, long double maxVal);
void test_floating(const char* label, long double maxVal);
void print_max(const char* label, unsigned n);
void cleanUp(Primes* p);
void prtPrms(const Primes*);

// Menu Function
int main() {
    int choice = 0;

    do {
        cout << "\nPlease choose a program/question below:\n";
        cout << "1. Bank Account\n";
        cout << "2. Gross Paychecks\n";
        cout << "3. Mean/Median/Mode\n";
        cout << "4. Data Encryption\n";
        cout << "5. Max n! Data Types\n";
        cout << "6. Conversion to NASA 4 Byte Float Format\n";
        cout << "7. Prime Number Factoring\n";
        cout << "8. Exit\n";
        cout << "\nEnter your choice (1-8): ";
        cin >> choice;

        if (!cin.good()) {
            invalidInput("Invalid input. Please try again.");
            continue;
        }

        switch (choice) {
            case 1:
                program_1();
                break;
            case 2:
                program_2();
                break;
            case 3:
                program_3();
                break;
            case 4:
                program_4();
                break;
            case 5:
                program_5();
                break;
            case 6:
                program_6();
                break;
            case 7:
                program_7();
                break;
            case 8:
                break;
            default:
                invalidInput("Invalid entry. Please try again.");
                break;

        }

    } while (choice != 8);

    cout << "\nThanks for viewing! Press Enter to end program.\n";
    clearInputBuffer();
    cin.get(); 
}

// Program 1 Execution
void program_1() {

    // Create Random Seed (set for random starting balance)
    srand(static_cast<unsigned int>(time(0)));

    // Create Account
    Account account;

    // Get Account Details
    account.accountNum = getAccountNumber("Enter 5 Digit Account Number: ");
    account.name = validateAccountDetails("Verify Account Holder's Name: ");
    account.address = validateAccountDetails("Verify Account Holder's Address: ");
    account.initBalance = initBalance("Current Balance of the Account: ");
    account.balance = account.initBalance;

    // Show what we captured
    displayAccount(account);
    bankAccountMenu(account);

    // Exit Stage Right
    cout << "\nPress Enter to return to program menu.\n";
    clearInputBuffer();
    cin.get(); 
    delete [] account.checks;
    delete [] account.deposits;
    account.checks = nullptr;
    account.deposits = nullptr;
    account.checkCount = 0;
    account.depositCount = 0;
    
    return;

}

// Program 2 Execution
void program_2() {

    // Designate Number of Companies
    int companyCount = 0;
    Company* companies = createCompanies(companyCount);
    if (!companies) return; 

    // Designate Employees
    Employee** roster = nullptr;
    int* employeeCount = nullptr;
    createEmployees(companies, companyCount, roster, employeeCount);

    // Exit Stage Right
    generateChecks(companies, roster, employeeCount, companyCount);
    cout << "\nPress Enter to return to program menu.\n";
    clearInputBuffer();
    cin.get(); 
    deleteCompanyData(companies, roster, employeeCount, companyCount);

    return;

}

// Program 3 Execution 
void program_3() {
    cout << "\nIncluded in another project (Problem_3)\n" << endl;
    cout << "\nPress Enter to return to program menu.\n";
    clearInputBuffer();
    cin.get(); 
    return;
}

// Program 4 Execution
void program_4() {

    string num;
    int choice = 0;

    do {
        cout << "\nPlease choose an option below:\n";
        cout << "1. Encrypt Number\n";
        cout << "2. Decrypt Number\n";
        cout << "3. Exit\n\n";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nEncrypt number selected.\n";
                encryptNumber();
                break;
            case 2:
                cout << "\nDecrypt number selected.\n";
                decryptNumber();
                break;
            case 3:
                cout << "\nExit\n";
                break;
            default:
                invalidInput("Invalid input. Please try again.");
                break;
        }

    } while (choice != 3);

    cout << "\nPress Enter to return to program menu.\n";
    clearInputBuffer();
    cin.get(); 
    
    return;
}

// Program 5 Execution
void program_5() {

    cout << "Max n where n! fits in each primitive type\n\n";

    test_integer("signed char", numeric_limits<signed char>::max());
    test_integer("unsigned char", numeric_limits<unsigned char>::max());
    test_integer("short", numeric_limits<short>::max());
    test_integer("unsigned short", numeric_limits<unsigned short>::max());
    test_integer("int", numeric_limits<int>::max());
    test_integer("unsigned int", numeric_limits<unsigned int>::max());
    test_integer("long", numeric_limits<long>::max());
    test_integer("unsigned long", numeric_limits<unsigned long>::max());
    test_integer("long long", numeric_limits<long long>::max());
    test_integer("unsigned long long", numeric_limits<unsigned long long>::max());
    test_floating("float", numeric_limits<float>::max());
    test_floating("double", numeric_limits<double>::max());
    test_floating("long double", numeric_limits<long double>::max());

    // Exit Stage Right
    cout << "\nPress Enter to return to program menu.\n";
    clearInputBuffer();
    cin.get(); 
    return;
    
}

// Program 6 Execution
void program_6() {
    const int cols_a_b = 5;
    const int rows_a = 3;
    const int rows_b = 3;
    const int cols_c = 2;
    const int rows_c = 3;

    cout << "Float Conversion Result Table\n\n" << endl;

    // Column headers
    string headersAB[cols_a_b] = { "Base 10", "Base 2", "Base 8", "Base 16", "NASA" };
    string headersC[cols_c] = { "Float", "Base 10"};

    // Part A - Positive values
    string tableA[rows_a][cols_a_b] = {
        { "49.1875",    "110001.0011", "61.14",  "31.3",  "0xC4C00006" },
        { "3.07421875", "11.00010011", "3.046",  "3.13",  "0xC4C00002" },
        { "0.2",        "0.0011",      "0.1463", "0.3",   "0xCCCCCCFE" }
    };

    // Part B - Negative values
    string tableB[rows_b][cols_a_b] = {
        { "-49.1875",    "-110001.0011", "-61.14",  "-31.3",  "0x3B400006" },
        { "-3.07421875", "-11.00010011", "-3.046",  "-3.13",  "0x3B400002" },
        { "-0.2",        "-0.0011",      "-0.1463", "-0.3",   "0x333334FE" }
    };

    // Part C - Float representation to decimal
    string tableC[rows_c][cols_c] = {
        { "69999902", "3.29688"},
        { "69999903", "6.59376"},
        { "966667FF", "-0.2062449"}
    };

    // Print Part A
    cout << "\nPart A - Positive Values\n\n";

    for (int j = 0; j < cols_a_b; j++) {
        cout << left << setw(15) << headersAB[j];
    }

    cout << endl << string(75, '-') << endl;

    for (int i = 0; i < rows_a; i++) {

        for (int j = 0; j < cols_a_b; j++) {
            cout << left << setw(15) << tableA[i][j];
        }

        cout << endl;
    }

    // Print Part B
    cout << "\nPart B - Negative Values\n\n";

    for (int j = 0; j < cols_a_b; j++) {
        cout << left << setw(15) << headersAB[j];
    }

    cout << endl << string(75, '-') << endl;

    for (int i = 0; i < rows_b; i++) {

        for (int j = 0; j < cols_a_b; j++) {
            cout << left << setw(15) << tableB[i][j];
        }    
        cout << endl;

    }

    // Print Part C

    cout << "\nPart C - Convert Float Representation to Decimal\n\n";

    for (int j = 0; j < cols_c; j++) {
        cout << left << setw(25) << headersC[j];
    }
    
    cout << endl << string(50, '-') << endl;

    for (int i = 0; i < rows_c; i++) {
        
        for (int j = 0; j < cols_c; j++) {
            cout << left << setw(25) << tableC[i][j];
        }   
        cout << endl;

    }

    cout << "\nPress Enter to return to program menu.\n";
    clearInputBuffer();
    cin.get(); 
}

// Program 7 Execution
void program_7() {
    int num;
    validatePrimeInput(num);   

    Primes* pf = factor(num);
    prtPrms(pf);
    cleanUp(pf);

    // Exit Stage Right
    cout << "\nPress Enter to return to program menu.\n";
    clearInputBuffer();
    cin.get();
    return;
}

// Clear Leftovers
void clearInputBuffer() {
    cin.ignore(10000, '\n');
}

// Invalid Inputs
void invalidInput(const string &prompt) {
    cin.clear();
    clearInputBuffer();
    cout << prompt << "\n";
}

// Validate the Account Number
unsigned int getAccountNumber(const string &prompt) {

    unsigned int num;
    bool validID = false;

    do {
        cout << prompt;
        cin >> num;

        if (!cin.good()) {
            invalidInput("Invalid input. Please try again.");
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
            invalidInput("Invalid input. Please try again.");
            continue;
        } else {
            valid = true;
        }

    } while (!valid);

    return input;
}

float initBalance(const string &prompt) {
    bool valid = false;
    float initBalance;

    do {
        cout << prompt;
        cin >> initBalance;

        if (!cin.good()) {
            invalidInput("Invalid input. Please try again.");
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
            invalidInput("Invalid input. Please try again.");
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
                invalidInput("Invalid entry. Please try again.");
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
            invalidInput("Invalid input. Please try again.");
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
            invalidInput("Invalid input. Please try again.");
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

// Set up Company
Company* createCompanies(int &companyCount) {

    cout << "How many companies? ";

    if (!(cin >> companyCount) || companyCount <= 0) {
        invalidInput("Invalid input. Please try again.");
        return nullptr;
    }

    Company* companies = new Company[companyCount];
    clearInputBuffer();

    for (int i = 0; i < companyCount; ++i) {

        cout << "\n=== Company #" << (i + 1) << " ===\n\n";
        
        // Company Name
        cout << setw(10) << left << "Name: ";      
        getline(cin, companies[i].name);
        
        // Company Address
        cout << setw(10) << left << "Address: ";   
        getline(cin, companies[i].address);
        cout << setw(10) << left << "City: ";
        getline(cin, companies[i].city);
        cout << setw(10) << left << "State: ";
        getline(cin, companies[i].state);
        cout << setw(10) << left << "ZIP: ";
        getline(cin, companies[i].zip);
    
    }

    return companies;

}

// Create Employee Array for Each Company
void createEmployees(Company* companies, int companyCount, Employee** &roster, int* &employeeCount) {

    // [i][j] = [company][employee]

    roster = new Employee*[companyCount];
    employeeCount = new int[companyCount];

    for (int i = 0; i < companyCount; ++i) {

        cout << "\nHow many employees for " << companies[i].name << "? ";

        if (!(cin >> employeeCount[i]) || employeeCount[i] < 0) {

            invalidInput("Invalid input. Please try again.");

            employeeCount[i] = 0;
            roster[i] = nullptr;

            return;

        }

        roster[i] = (employeeCount[i] > 0) ? new Employee[employeeCount[i]] : nullptr;

        cout << "\n=== " << companies[i].name << " Employees === \n";

        if ((employeeCount[i]) == 0) {
            cout << "\nNo Employees work here";
            continue;    
        }

        for (int j = 0; j < employeeCount[i]; ++j) {
            clearInputBuffer();

            cout << "\nEmployee #" << (j + 1) << "\n";
            cout << "Name: ";
            getline(cin, roster[i][j].name);

            cout << "Hours Worked: ";
            if (!(cin >> roster[i][j].hours)) {

                invalidInput("Invalid input. Please try again.");
                employeeCount[i] = j; 
                
                return;
            }

            cout << "Rate of Pay: ";
            if (!(cin >> roster[i][j].rate)) {

                invalidInput("Invalid input. Please try again.");
                employeeCount[i] = j; 

                return;
            }

            roster[i][j].gross = computeGross(roster[i][j].hours, roster[i][j].rate);
        }
    }
}

// Calculate Gross Paycheck Per Employee
float computeGross(float hours, float rate) {
    if (hours <= 0 || rate <= 0) {
        return -1; 
    }

    if (hours <= 40)
        return hours * rate;
    else if (hours <= 50)
        return (40 * rate) + ((hours - 40) * rate * 2);
    else
        return (40 * rate) + (10 * rate * 2) + ((hours - 50) * rate * 3);
}

// Convert Gross Pay to English 
string chunkToText(int n) {

    static const string uniqueNumbers[] = {
        "Zero",
        "One",
        "Two",
        "Three",
        "Four",
        "Five",
        "Six",
        "Seven",
        "Eight",
        "Nine",
        "Ten",
        "Eleven",
        "Twelve",
        "Thirteen",
        "Fourteen",
        "Fifteen",
        "Sixteen",
        "Seventeen",
        "Eighteen",
        "Nineteen"
    };

    static const string tensNumbers[] = {
        "", // Zeros
        "", // Tens
        "Twenty",
        "Thirty",
        "Forty",
        "Fifty",
        "Sixty",
        "Seventy",
        "Eighty",
        "Ninety"
    };

    string out;

    if (n >= 100) {

        out += uniqueNumbers[n / 100] + " Hundred";
        n %= 100;
        if (n) out += " ";

    }

    if (n >= 20) {

        out += tensNumbers[n / 10];
        if (n % 10) out += "-" + uniqueNumbers[n % 10];

    } else if (n > 0) {

        out += uniqueNumbers[n];

    }

    return out;
}

// Convert Numerical Value to Words
string getAmountInWords(float amount) {

    int dollars = static_cast<int>(amount);
    int cents   = static_cast<int>((amount - dollars) * 100 + 0.5);
    if (cents == 100) { dollars += 1; cents = 0; }

    string words;

    // Are We A Millionare?
    int millions = dollars / 1000000;
    dollars %= 1000000;

    // Did We Hit 6 Figures?
    int thousands = dollars / 1000;
    dollars %= 1000;

    // I Guess Not
    int units = dollars;

    if (millions)  
        words += (words.empty() ? "" : " ") + chunkToText(millions) + " Million";

    if (thousands) 
        words += (words.empty() ? "" : " ") + chunkToText(thousands) + " Thousand";

    if (units)
        words += (words.empty() ? "" : " ") + chunkToText(units);

    if (words.empty()) 
        words = "Zero";

    // Compose Cents in English
    string c = (cents < 10) ? ("0" + to_string(cents)) : to_string(cents);

    return words + " and " + c + "/100 Dollars";

}

// Generate Our Paychecks for Each Valid Timecard
void generateChecks(Company* companies, Employee** roster, int* employeeCount, int companyCount) {

    cout << "\n\n*** Paychecks ***\n";

    unsigned int checksMade = 0;
    string successMsg;

    for (int i = 0; i < companyCount; ++i) {

        for (int j = 0; j < employeeCount[i]; ++j) {
            const Employee& employee = roster[i][j];

            // Check Formatting
            cout << "\nCompany: " << companies[i].name << '\n';
            cout << "Address: " << companies[i].address << ", " << companies[i].city << ", " << companies[i].state << " " << companies[i].zip << '\n';

            // No Checks for Invalid Entries
            if (employee.gross <= 0 || employee.rate <= 0) {
                cout << "No check can be made out to " << employee.name << ".\n";
                continue;
            }

            cout << fixed << setprecision(2);
            cout << "Name: " << employee.name << "  Amount: $" << employee.gross << '\n';
            cout << "Amount: " << getAmountInWords(employee.gross) << '\n';
            cout << "Signature Line: __________________________\n";

        }

    }

    // Confirm Check Creation
    (checksMade > 0) ? successMsg = "\nAll paychecks created successfully.\n" : "\n No paychecks were created.\n"; 
    cout << successMsg;

}

// Delete Company Data
void deleteCompanyData(Company* companies, Employee** roster, int* employeeCount, int companyCount) {
    
    if (roster != nullptr) {
        for (int i = 0; i < companyCount; ++i)
            delete[] roster[i];
        delete[] roster;
    }
    
    delete[] employeeCount;
    delete[] companies;

}

// Encrypt number
void encryptNumber() {

    string num;

     // Prompt
    cout << "\nEncrypt a four integer number. Integers must be between 0-7: ";
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
    outputNum(num, "Your encrypted number: ");

}

void decryptNumber() {
    
    string num;

    // Prompt
    cout << "\nDecrypt a four integer number. Integers must be between 0-7: ";
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
    }

    // Output Decrypted Number
    outputNum(num, "Your decrypted number: ");
}

// Validate Encrypt/Decrypt Entry
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
            invalidInput("Input must contain numbers between 0-7.");
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

// Test Integers for Max N 
void test_integer(const char* label, long double maxVal) {
    
    // Unsigned long long will house the biggest factorial
    unsigned long long factorial = 1;

    // Integer
    unsigned n = 1;

    // Stop when (n + 1)! would exceed the type's max
    while (static_cast<long double>(factorial) <= maxVal / (n + 1)) {
        factorial *= (n + 1);
        ++n;
    }

    print_max(label, n);
}

// Test Decimals for Max N
void test_floating(const char* label, long double maxVal) {

    // Long double will house the biggest factorial for decimals
    long double factorial = 1.0L;
    
    // Integer
    unsigned n = 1;

    // Stop when (n + 1)! would exceed the type's max
    while (factorial <= maxVal / (n + 1)) {
        factorial *= (n + 1);
        ++n;
    }

    print_max(label, n);
}

// Print Max N Result
void print_max(const char* label, unsigned n) {
    cout << setw(20) << left << label << " : max n = " << n << "\n";
}

// Determine if the number is Prime
bool isPrime(int num) {

    // If it's even, it can only be prime if it's exactly 2
    if (num == 2) return true;

    // If it's even but not 2, then not prime
    if (num % 2 == 0) return false;

    // Test all odd numbers (3-7 fall through aren't checked here)
    for (int odd = 3; odd * odd <= num; odd += 2) {
        if (num % odd == 0) return false;
    }

    // All other numbers are prime
    return true;
}

// What power is this factor and remove from n
int power(int factor, int &num) {
    int exponent = 0;

    // Divide by factor until remainder
    while (num % factor == 0) {
        num /= factor;
        ++exponent;
    }

    return exponent;
}

// Distinct Primes
int nPrimes(int num) {
    int distinctPrimes = 0;

    // Prime factor 2
    if (num % 2 == 0) {
        ++distinctPrimes;

        while (num % 2 == 0) {
            num /= 2;
        }
    }

    // Odd Prime Factors
    for (int odd = 3; odd * odd <= num; odd += 2) {

        if (num % odd == 0) {

            ++distinctPrimes;

            while (num % odd == 0) {
                num /= odd;
            }

        }
    }

    // Fall through for odds 3-7
    if (num > 1) ++distinctPrimes;

    return distinctPrimes;
}

// Prime Factors
Primes* factor(int num) {

    // Create Pointer
    Primes* res = new Primes;

    // Deref pointer
    Primes &r = *res; 

    // Store original number
    r.n = num;

    // Make a copy
    int tmp = num;

    // Get distinct primes
    r.nPrimes = nPrimes(tmp);

    // Create array for prime factors
    r.pStrAry = new Prime[r.nPrimes];

    // Copy num for factoring
    int n = num;
    int i = 0;

    for (int d = 2; d * d <= n && i < r.nPrimes; ++d) {

        if (isPrime(d)) {

            int k = power(d, n);

            // Record if d divides n at least once 
            if (k > 0) {

                r.pStrAry[i].prime = d;    
                r.pStrAry[i].power = k;
                ++i;

            }
        }
    }

    // Leftover is a prime factor itself
    if (n > 1 && i < r.nPrimes) {
        r.pStrAry[i].prime = n;
        r.pStrAry[i].power = 1;
        ++i;
    }

    return res;
}

// Print Primes
void prtPrms(const Primes* P) {

    // Deref structure pointer
    const Primes &r = *P;

    // Display original number
    cout << r.n << " = ";

    // Display prime factors
    for (int i = 0; i < r.nPrimes; ++i) {

        cout << r.pStrAry[i].prime << "^" << static_cast<int>(r.pStrAry[i].power);
        if (i + 1 < r.nPrimes) cout << " * ";
    }

    // Move to a new line after printing the entire expression
    cout << '\n';
}

// Input Validation
bool validatePrimeInput(int &num) {
    bool valid = false;

    do {
        cout << "\nInput a number (2 - 65000) to find its prime factors: ";
        cin >> num;

        if (!cin.good()) {
            invalidInput("Invalid input.");
        } else if (num < 2 || num > 65000) {
            invalidInput("Not in valid range (2 - 65000).");
        } else {
            valid = true; 
        }

    } while (!valid);

    return true;
}

// Delete Data
void cleanUp(Primes* p) { 
    if (p) { 
        Primes &r = *p;     
        delete[] r.pStrAry; 
        delete p; 
    } 
}