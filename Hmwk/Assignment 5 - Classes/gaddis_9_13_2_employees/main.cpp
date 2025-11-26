/*
 * File:   main.cpp
 * Author: John Huynh
 * Date:   November 24, 2025
 * Purpose: Employee Class and Info Display
*/

// Libraries
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Employee {

    private:
        string name;
        int idNumber;
        string department;
        string position;

    public:
        Employee(string n, int id, string dept, string pos) {
            name = n;
            idNumber = id;
            department = dept;
            position = pos;
        }

        // Initialized Employee Data
        Employee(string n, int id) {
            name = n;
            idNumber = id;
            department = "";
            position = "";
        }

        // Default Employee Data
        Employee() {
            name = "";
            idNumber = 0;
            department = "";
            position = "";
        }

        // Mutators
        void sName(string n) { 
            name = n;
        }
        void sIdNumber(int id) { 
            idNumber = id;
        }
        void sDepartment(string dept) { 
            department = dept;
        }
        void sPosition(string pos) { 
            position = pos;
        }

        string employeeName() const { 
            return name;
        }
        int employeeID() const { 
            return idNumber;
        }
        string employeeDept() const { 
            return department;
        }
        string employeePos() const { 
            return position;
        }

        void display() const {
            cout << left << setw(20) << name << setw(15) << idNumber << setw(20) << department << setw(20) << position << endl;
        }
};

// Main Function
int main() {

    Employee susan("Susan Meyers", 47899, "Accounting", "Vice President");
    Employee mark("Mark Jones", 39119, "IT", "Programmer");
    Employee joy("Joy Rogers", 81774, "Manufacturing", "Engineer");

    // Display Data
    cout << left << setw(20) << "Name" << setw(15) << "ID Number" << setw(20) << "Department" << setw(20) << "Position" << endl;

    susan.display();
    mark.display();
    joy.display();

    // Exit Stage Right
    cin.get();
    return 0;
}