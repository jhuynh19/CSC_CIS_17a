/* 
 * File: main.cpp
 * Author: John Huynh
 * Created on 12/04/2025
 * Purpose: MilTime Class with nested exception handling (Chapter 16, Problem 2)
 */

// Libraries
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Time {
    protected: 
        int hour; 
        int min; 
        int sec;

    public:
        // Default Constructor
        Time() : hour(0), min(0), sec(0) {}
        
        // Parameterized
        Time(int h, int m, int s) : hour(h), min(m), sec(s) {}
    
        // Mutator
        void setTime(int h, int m, int s) {
            hour = h;
            min = m;
            sec = s;
        }

        // Getters
        int getHour() const {
            return hour;
        }
        int getMin() const {
            return min;
        }
        int getSec() const {
            return sec;
        }
};

class MilTime : public Time {
    public:
        class BadHour { }; 
        class BadSeconds { };

    private:
        int milHours;  
        int milSeconds; 

        // Convert Mil Time to Std Time (assumes input has been validated)
        void convert() {
            
            // Separate hours and minutes
            int militaryHour = milHours / 100;
            int minutes = milHours % 100;

            // Convert the hour
            int standardHour;
            if (militaryHour == 0) {
                standardHour = 12;
            } else if (militaryHour > 12) {
                standardHour = militaryHour - 12; 
            } else {
                standardHour = militaryHour; 
            }
            
            // Feed values to Time
            Time::setTime(standardHour, minutes, milSeconds);
        }

    public:
        // Default Constructor
        MilTime() : Time(), milHours(0), milSeconds(0) {}

        // Parameterized Constructor
        MilTime(int milHr, int milSec) : Time() {
            setTime(milHr, milSec); // Use setTime for combined validation/conversion logic
        }

        // Getters
        int getMilHour() const { return milHours; }
        int getStandHr() const { return hour; }
        int getMilSeconds() const { return milSeconds; }

        string getPeriod() const {
            if (milHours >= 1200 && milHours <= 2359) {
                return "PM";
            } else {
                return "AM";
            }
        }
        
        // Mutator
        void setTime(int milHr, int milSec) {
            
            // Validate Seconds
            if (milSec < 0 || milSec > 59) {
                throw BadSeconds();
            }

            // Validate Hours component
            if (milHr < 0 || milHr > 2359) {
                throw BadHour();
            }
            
            // Validate Minutes component
            int minutes = milHr % 100;
            if (minutes < 0 || minutes > 59) {
                throw BadHour(); 
            }

            // If validation passes
            milHours = milHr;
            milSeconds = milSec;
            convert();
        }
};

// Main
int main() {
    
    try {
        cout << "Test 1: 800, 30" << endl;
        MilTime validTime(800, 30);
        cout << "Standard Time: " << validTime.getStandHr() << ":" << setfill('0') << setw(2) << validTime.getMin() << ":" << setfill('0') << setw(2) << validTime.getSec() << " " << validTime.getPeriod() << endl;
    }
    catch (...) {}

    cout << "\nTest 2: 2400, 30" << endl;
    try {
        MilTime badHour(2400, 30);
    }
    catch (MilTime::BadHour) { 
        cout << "Err: Invalid hours. Hours must be between 0000 and 2359." << endl;
    }

    cout << "\nTest 3: 1000, 65" << endl;
    try {
        MilTime badSeconds(1000, 65);
    }
    catch (MilTime::BadSeconds) { 
        cout << "Err: Invalid seconds. Seconds must be between 0 and 59." << endl;
    }

    cout << "\nTest 4: 1265, 0" << endl;
    try {
        MilTime badMinutes(1265, 0); 
    }
    catch (MilTime::BadHour) { 
        cout << "Err: Invalid minutes. Must be between 0-59." << endl;
    }
    
    // Exit stage right
    cin.get();
    return 0;
}