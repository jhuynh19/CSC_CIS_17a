/* 
 * File: main.cpp
 * Author: John Huynh
 * Created on 12/03/2025
 * Purpose: Time Class and MilTime Child Class
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
    private:
        int milHours;  
        int milSeconds; 

        // Convert Mil Time to Std Time
        void convert() {
            
            // Separate hours and minutes
            int militaryHour = milHours / 100;
            int minutes = milHours % 100;

            // Convert the hour
            int standardHour;

            if (militaryHour == 0) {
                standardHour = 12;
            } 
            else if (militaryHour > 12) {
                standardHour = militaryHour - 12; 
            } 
            else {
                standardHour = militaryHour; 
            }
            
            // Feed values to Time
            Time::setTime(standardHour, minutes, milSeconds);
        }
        
        // Check valid input
        bool isValid(int milHr, int milSec) const {
            int minutes = milHr % 100;

            if (milHr < 0 || milHr > 2359 || milSec < 0 || milSec > 59) return false;
            if (minutes < 0 || minutes > 59) return false;
            
            return true;
        }

    public:
        MilTime(int milHr, int milSec) : Time() {
            if (isValid(milHr, milSec)) {
                milHours = milHr;
                milSeconds = milSec;
                convert();
            } else {
                milHours = 0;
                milSeconds = 0;
                convert();
                cout << "Err: Invalid input. Time set to 0000:00." << endl;
            }
        }
        
        // Default Constructor
        MilTime() : Time(), milHours(0), milSeconds(0) {}

        // Getters
        int getMilHour() const { 
            return milHours; 
        }
        int getStandHr() const { 
            return hour;
        }
        int getMilSeconds() const {
            return milSeconds;
        }

        // Mutator
        void setTime(int milHr, int milSec) {
            if (isValid(milHr, milSec)) {
                milHours = milHr;
                milSeconds = milSec;
                convert();
            } else {
                cout << "Err: setTime failed." << endl;
            }
        }
};


// Main
int main() {
    int milH, milS;
    string period;
    
    // Get inputs
    cout << "Enter the time in military format: ";
    cin >> milH;
    
    cout << "Enter the seconds: ";
    cin >> milS;

    // Create object
    MilTime currentTime(milH, milS); 
    
    if (currentTime.getMilHour() >= 1200 && currentTime.getMilHour() <= 2359) {
        period = "PM";
    } else {
        period = "AM";
    }
    
    // Military Time Output
    cout << "Military Time: " << setfill('0') << setw(4) << currentTime.getMilHour() << setfill('0') << setw(2) << currentTime.getSec() << endl;
    
    // Regular Time Output
    cout << "Standard Time: " << currentTime.getStandHr() << ":" << setfill('0') << setw(2) << currentTime.getMin() << ":" << setfill('0') << setw(2) << currentTime.getSec() << " " << period << endl;

    //Exit stage right
    cin.ignore(); 
    cin.get();
    return 0;
}