/*
 * File: main.cpp
 * Author: John Huynh
 * Date: November 25, 2025
 * Purpose: Date of Year Based on String Input
 */

// Libraries
#include <iostream>
#include <string>
#include <cstdlib> 

using namespace std;

class DayOfYear {

    private:
        int dayOfYear;
        static string monthNames[12];
        static int daysInMonth[12];

    public:

        DayOfYear(string month, int day) {

            int monthIndex = -1;

            /* Validate Month in Input */
            for (int i = 0; i < 12; i++) {
                if (month == monthNames[i]) {
                    monthIndex = i;
                    break;
                }
            }

            if (monthIndex == -1) {
                cout << "Err: '" << month << "' is not a valid month name.\n";
                exit(0); 
            }

            /* Validate Day in Month */
            if (day < 1 || day > daysInMonth[monthIndex]) {
                cout << "Err: " << month << " only has " << daysInMonth[monthIndex] << " days.\n";
                exit(0); 
            }

            /* Day of Year */
            dayOfYear = day;
            for (int i = 0; i < monthIndex; i++) {
                dayOfYear += daysInMonth[i];
            }
        }

        /* Wrap forward to Start */
        DayOfYear& operator++() {
            dayOfYear++;
            if (dayOfYear > 365) {
                dayOfYear = 1; 
            }
            return *this;
        }

        /* Postfix Increment */
        DayOfYear operator++(int) {
            DayOfYear temp = *this; 
            ++(*this);             
            return temp;
        }

        /* Wrap back to End */
        DayOfYear& operator--() {
            dayOfYear--;
            if (dayOfYear < 1) {
                dayOfYear = 365; 
            }
            return *this;
        }

        /* Postfix Decrement */
        DayOfYear operator--(int) {
            DayOfYear temp = *this;
            --(*this);
            return temp;
        }

        // Print Date
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

    cout << "December 31: \n";
    DayOfYear nye("December", 31);
    
    cout << "Original: ";
    nye.print();
    ++nye; 

    cout << "Next Day: ";
    nye.print();

    cout << "\nJanuary 1: \n";
    DayOfYear nyd("January", 1);
    
    cout << "Original: ";
    nyd.print();
    nyd--;
    
    cout << "Previous Day: ";
    nyd.print(); 

    cout << "\nFebruary 29: ";
    DayOfYear badDate("February", 29);
    badDate.print(); 

    // Exit Stage Right
    cin.get();
    return 0;
}