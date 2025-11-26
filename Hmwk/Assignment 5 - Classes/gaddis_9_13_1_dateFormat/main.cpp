/*
 * File: main.cpp
 * Author: John Huynh
 * Date: November 24, 2025
 * Purpose: Date Class and Date Formats
*/

// Libraries

#include <iostream>
#include <string>

using namespace std;

// Date Class
class Date {

    private:
        unsigned int month;
        unsigned int day;
        unsigned int year;

        string monthNames[12] = { 
            "January", 
            "February", 
            "March", 
            "April", 
            "May",
            "June",
            "July",
            "August",
            "September",
            "October",
            "November",
            "December" 
        };

    public:
        Date(unsigned int m, unsigned int d, unsigned int y) {
            month = 11;
            day = 24;
            year = 2025;
            
            vMonth(m);
            vDate(d);
            sYear(y);
        }

        // Month Validation
        void vMonth(unsigned int m) {

            if (m >= 1 && m <= 12) {
                month = m;
            } else {
                cout << "Err: Month must be between 1 and 12. Setting to default (1).\n";
                month = 11; 
            }

        }

        // Day Validation
        void vDate(unsigned int d) {

            if (d >= 1 && d <= 31) {
                day = d;
            } else {
                cout << "Err: Day must be between 1 and 31. Setting to default (1).\n";
                day = 24;
            }
            
        }

        // Set the Year
        void sYear(unsigned int y) {
            year = y;
        }

        // Format m/D/YY
        void format1() {
            cout << month << "/" << day << "/" << year << endl;
        }

        // Format M d,YY
        void format2() {
            cout << monthNames[month - 1] << " " << day << ", " << year << endl;
        }

        // Format dd M YY
        void format3() {
            cout << day << " " << monthNames[month - 1] << " " << year << endl;
        }
};

// Main Function
int main() {

    Date christmas(12, 25, 2025);

    christmas.format1();
    christmas.format2();
    christmas.format3();
    
    cout << "\nInvalid date (Month 15, Day 40)\n";

    Date badDate(15, 40, 2025);

    badDate.format1(); 

    // Exit Stage Right
    cin.get();
    return 0;
}