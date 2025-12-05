/* 
 * File: main.cpp
 * Author: John Huynh
 * Created on 12/01/2025
 * Purpose: Create Employee Class and ProductionWorker Child Class
*/

// Libraries
#include <iostream>
#include <string>

using namespace std;

class Employee {
    private:
        string name;
        int number;
        string hireDate;

    public:
        Employee(string empName, int empNumber, string date) {
            name = empName;
            number = empNumber;
            hireDate = date;
        }

        // Constructor
        Employee() : name(""), number(0), hireDate("") {}

        // Mutators
        void setName(string empName) {
            name = empName;
        }
        void setNumber(int empNumber) {
            number = empNumber;
        }
        void setHireDate(string date) {
            hireDate = date;
        }

        // Getters
        string getName() const {
            return name;
        }
        int getNumber() const {
            return number;
        }
        string getHireDate() const {
            return hireDate;
        }
};

class ProductionWorker : public Employee {
    private:
        int shift;
        double payRate;

    public:
        ProductionWorker(string n, int num, string date, int s, double rate) : Employee(n, num, date) {
            shift = s;
            payRate = rate;
        }

        // Default constructor
        ProductionWorker() : Employee(), shift(0), payRate(0.0) {}

        // Mutators
        void setShift(int s) {
            shift = s;
        }
        void setPayRate(double rate) {
            payRate = rate;
        }

        // Getters
        int getShift() const {
            return shift;
        }
        string getShiftName() const {
            string shiftName;
            switch (shift) {
                case 1:
                    shiftName = "Day";
                    break;
                case 2:
                    shiftName = "Night";
                    break;
                default:
                    shiftName = "Invalid Shift";
            }
            return shiftName;
        }
        double getPayRate() const {
            return payRate;
        }
};

// Main
int main() {
    float payRaise;

    // Create Object
    ProductionWorker john("John Huynh", 113, "01/10/17", 1, 28);

    // Output
    cout << "Employee Name: " << john.getName() << endl; 
    cout << "Employee Number: " << john.getNumber() << endl; 
    cout << "Hire Date: " << john.getHireDate() << endl; 
    cout << "Shift: " << john.getShiftName() << " (" << john.getShift() << ")" << endl;
    cout << "Pay Rate: $" << john.getPayRate() << endl;
    
    // Update Pay
    cout << "\nUpdate Pay for " << john.getName() << ": ";
    cin >> payRaise;
    john.setPayRate(payRaise);
    cout << "\n\nUpdated Pay Rate: $" << john.getPayRate() << endl;

    //Exit stage right
    cin.get();
    return 0;
}