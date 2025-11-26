/*
 * File: main.cpp
 * Author: John Huynh
 * Date: November 24, 2025
 * Purpose: Employee Class and Info Display
*/

// Libraries
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class familyMember {

    private:
        string name;
        string address;
        int age;
        string phoneNumber;

    public:
        familyMember(string n, string ad, int a, string phone) {
            name = n;
            address = ad;
            age = a;
            phoneNumber = phone;
        }

        // Default Family Member Data
        familyMember() {
            name = "";
            address = "";
            age = 0;
            phoneNumber = "";
        }

        //  Mutators
        void firstName(string n) { 
            name = n;
        }
        void sAddress(string ad) { 
            address = ad;
        }
        void sAge(int a) { 
            age = a;
        }
        void sPhoneNumber(string phone) { 
            phoneNumber = phone;
        }

        string firstName() const { 
            return name;
        }
        string address() const { 
            return address;
        }
        int age() const { 
            return age;
        }
        string phone() const { 
            return phoneNumber;
        }

        void display() const {
            cout << "Name: " << name << "\n";
            cout << "Address: " << address << "\n";
            cout << "Age: " << age << "\n";
            cout << "Phone: " << phoneNumber << "\n\n";
        }

};

int main() {

    familyMember john("John Huynh", "127 Main St.", 28, "(123) 456-7890");
    familyMember ryan("Ryan Huynh", "7177 Lorelain Ave.", 25, "(951) 545-0837");
    familyMember aidan("Aidan Huynh", "331 2nd St. Apt 411", 22, "(214) 477-0737");

    // Display Family Members
    john.display();
    ryan.display();
    aidan.display();

    // Exit Stage Right
    cin.get();
    return 0;
}