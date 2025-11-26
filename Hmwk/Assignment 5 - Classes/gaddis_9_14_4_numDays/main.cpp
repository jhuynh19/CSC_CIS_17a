/*
 * File: main.cpp
 * Author: John Huynh
 * Date: November 26, 2025
 * Purpose: Convert Work Hours into Days
 */

// Libraries
#include <iostream>
#include <iomanip> 

using namespace std;

class NumDays {

    private:
        float hours; 

    public:
        NumDays(float h = 0) {
            hours = h;
        }

        // Mutators
        void setHours(float h) {
            hours = h;
        }

        float getHours() const {
            return hours;
        }

        /* 1 Day Equals 8 Hours */
        float getDays() const {
            return hours / 8.0;
        }

        /* Addition Operator */
        NumDays operator+(const NumDays &right) {
            return NumDays(this->hours + right.hours);
        }

        /* Subtraction Operator */
        NumDays operator-(const NumDays &right) {
            return NumDays(this->hours - right.hours);
        }

        /* Add Hour */
        NumDays operator++() {
            hours++; 
            return *this;
        }

        /* Postfix Increment */
        NumDays operator++(int) {
            NumDays temp = *this; 
            hours++;
            return temp;
        }

        /* Subtract Hour */
        NumDays operator--() {
            hours--; 
            return *this;
        }

        /* Postfix Decrement */
        NumDays operator--(int) {
            NumDays temp = *this; 
            hours--;
            return temp;
        }
};

// Main
int main() {
    
    cout << fixed << setprecision(2);

    NumDays worker1(12);
    NumDays worker2(18);

    cout << "Worker 1: " << worker1.getHours() << " hours (" << worker1.getDays() << " days)\n";
    cout << "Worker 2: " << worker2.getHours() << " hours (" << worker2.getDays() << " days)\n\n";

    /* Add Worker Hours */
    NumDays total = worker1 + worker2; 
    cout << "Total Hours: " << total.getHours() << " hours (" << total.getDays() << " days)\n\n";

    /* Difference in Hours */
    NumDays diff = worker2 - worker1;
    cout << "Difference in Hours: " << diff.getHours() << " hours (" << diff.getDays() << " days)\n\n";

    /* Increase Worker Hours */
    cout << "Original Hours (Worker 1): " << worker1.getHours() << " hours\n";
    worker1++; 
    cout << "New Hours: " << worker1.getHours() << " hours (" << worker1.getDays() << " days)\n";

    /* Decrease Worker Hours */
    cout << "\nOriginal Hours (Worker 2): " << worker2.getHours() << " hours\n";
    worker2--;
    cout << "New Hours: " << worker2.getHours() << " hours (" << worker2.getDays() << " days)\n";

    // Exit Stage Right
    cin.get();
    return 0;
}