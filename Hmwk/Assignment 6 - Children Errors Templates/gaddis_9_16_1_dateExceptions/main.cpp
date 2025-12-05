/* 
 * File: main.cpp
 * Author: John Huynh
 * Created on 12/04/2025
 * Purpose: Date Class with exception handling (Chapter 16, Problem 1)
*/

// Libraries
#include <iostream>
#include <string>

using namespace std;

// Date Class
class Date {
    
    public:
        class InvalidDay { };     
        class InvalidMonth { };   

    private:
        unsigned int month;
        unsigned int day;
        unsigned int year;

        string monthNames[12] = { 
            "January", "February", "March", "April", "May", "June",
            "July", "August", "September", "October", "November", "December" 
        };

    public:
        Date(unsigned int m, unsigned int d, unsigned int y) {
            month = 1; 
            day = 1;
            year = 2000;
            
            vMonth(m);
            vDate(d);
            sYear(y);
        }

        // Month Validation
        void vMonth(unsigned int m) {
            if (m >= 1 && m <= 12) {
                month = m;
            } else {
                throw InvalidMonth();
            }
        }

        // Day Validation
        void vDate(unsigned int d) {
            if (d >= 1 && d <= 31) {
                day = d;
            } else {
                throw InvalidDay();
            }
        }

        void sYear(unsigned int y) {
            year = y;
        }

        void format1() {
            cout << month << "/" << day << "/" << year << endl;
        }

        void format2() {
            cout << monthNames[month - 1] << " " << day << ", " << year << endl;
        }

        void format3() {
            cout << day << " " << monthNames[month - 1] << " " << year << endl;
        }
};

// Main Function
int main() {
    
    // Test Cases
    try { 
        cout << "Date 1: (12/25/2025)" << endl;
        Date christmas(12, 25, 2025);
        christmas.format1();
        
        cout << "Date 2: (13/10/2025)" << endl;
        Date badMonth(13, 10, 2025); 
    }
    catch (Date::InvalidMonth) { 
        cout << "Caught InvalidMonth: Month must be between 1 and 12." << endl;
    }
    try {
        cout << "Date 3: (2/33/2025)" << endl;
        Date badDay(2, 33, 2025); 
    }
    catch (Date::InvalidDay) { 
        cout << "Caught InvalidDay: Day must be between 1 and 31." << endl;
    }

    // Exit stage right
    cin.get();
    return 0;
}