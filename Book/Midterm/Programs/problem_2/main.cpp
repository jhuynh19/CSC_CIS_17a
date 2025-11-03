/* 
 * File:   main.cpp
 * Author: John Huynh
 * Created on October 27, 2025
 * 
 * Purpose: Create a payroll app that determines gross pay
 */


// System Libraries
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Structures
struct Company {
    string name, address, city, state, zip;
};

struct Employee {
    string name;
    float hours, rate, gross;
};

// Prototypes

Company* createCompanies(int &companyCount);
string chunkToText(int n);
string getAmountInWords(float amount);
float computeGross(float hours, float rate);
void createEmployees(Company* companies, int companyCount, Employee** &roster, int* &employeeCount);
void deleteCompanyData(Company* companies, Employee** roster, int* employeeCount, int companyCount);
void generateChecks(Company* companies, Employee** roster, int* employeeCount, int companyCount);
void clearInputBuffer();
void invalidInput(const string &prompt);

// Main Execution
int main() {

    // Designate Number of Companies
    int companyCount = 0;
    Company* companies = createCompanies(companyCount);
    if (!companies) return 0; 

    // Designate Employees
    Employee** roster = nullptr;
    int* employeeCount = nullptr;
    createEmployees(companies, companyCount, roster, employeeCount);

    // Exit Stage Right
    generateChecks(companies, roster, employeeCount, companyCount);
    cout << "\nPress Enter to Exit...";
    clearInputBuffer();
    cin.get(); 
    deleteCompanyData(companies, roster, employeeCount, companyCount);
    return 0;

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

// Delete Data
void deleteCompanyData(Company* companies, Employee** roster, int* employeeCount, int companyCount) {
    
    if (roster != nullptr) {
        for (int i = 0; i < companyCount; ++i)
            delete[] roster[i];
        delete[] roster;
    }
    
    delete[] employeeCount;
    delete[] companies;

}