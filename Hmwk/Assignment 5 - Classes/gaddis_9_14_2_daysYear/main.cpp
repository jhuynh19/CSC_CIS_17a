/*
 * File: main.cpp
 * Author: John Huynh
 * Date: November 25, 2025
 * Purpose: Date of Year Based on Day Input
*/

// Libraries
#include <iostream>
#include <string>

using namespace std;

// Day of Year Class
class DayOfYear {

    private:
        int dayOfYear;
        static string monthNames[12];
        static int daysInMonth[12];

    public:
        /* Validate Input */
        DayOfYear(int d) {
            if (d >= 1 && d <= 365) {
                dayOfYear = d;
            } else {
                cout << "Err: Day must be 1-365. Defaulting to 1.\n";
                dayOfYear = 1;
            }
        }

        /* Print Day of Year */
        void print() {
            int tempDay = dayOfYear;
            int monthIndex = 0;

            while (monthIndex < 12 && tempDay > daysInMonth[monthIndex]) {
                tempDay -= daysInMonth[monthIndex];
                monthIndex++;
            }

            cout << monthNames[monthIndex] << " " << tempDay << endl;
        }
};

string DayOfYear::monthNames[12] = {
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

int DayOfYear::daysInMonth[12] = {
    31,
    28,
    31,
    30,
    31,
    30,
    31,
    31,
    30,
    31,
    30,
    31
};

// Main
int main() {

    // February 14
    cout << "Valentines Day: ";
    DayOfYear valentines(45);
    valentines.print();

    // June 11
    cout << "HS Graduation: ";
    DayOfYear hs_graduation(162);
    hs_graduation.print();

    // July 15
    cout << "Birthday: ";
    DayOfYear birthday(196);
    birthday.print();

    cout << "Invalid Day: ";
    DayOfYear badDay(400); 
    badDay.print();

    // Exit Stage Right
    cin.get();
    return 0;
}