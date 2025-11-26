/*
 * File: main.cpp
 * Author: John Huynh
 * Date: November 26, 2025
 * Purpose: Car Fuel Gauge and Odometer
*/

#include <iostream>
#include <iomanip>

using namespace std;

class FuelGauge {
    private:
        int gallons;

    public:
        FuelGauge() { 
            gallons = 0; 
        }

        int getGallons() const { 
            return gallons; 
        }

        /* Add 1 gallon */ 
        void addGallons() {
            if (gallons < 15) {
                gallons++;
            }
        }

        /* Burn Gallon */
        void subtGallons() {
            if (gallons > 0) {
                gallons--;
            }
        }
};

class Odometer {
    private:
        int mileage, travelMiles; 
        const int MAX_MILES = 999999;
        const int MPG = 24;

    public:
        Odometer(int m = 0) { 
            mileage = m;
            travelMiles = 0; 
        }

        int getMileage() const { 
            return mileage; 
        }

        void addMile(FuelGauge &fuel) {
            
            mileage++;

            /* Reset Odometer */
            if (mileage > MAX_MILES) {
                mileage = 0;
            }

            travelMiles++;

            /* Subtract gallon if miles traveled equals MPG */
            if (travelMiles >= MPG) {
                fuel.subtGallons();
                travelMiles = 0; // Reset our internal counter
            }
        }
};

// Main Function
int main() {

    FuelGauge fuel;
    
    Odometer odo(999643); 

    for (int i = 0; i < 15; i++) {
        fuel.addGallons();
    }

    cout << "Tank is full: " << fuel.getGallons() << " gallons.\n\n";
    cout << "Time to drive...\n";
    
    while (fuel.getGallons() > 0) {
        
        odo.addMile(fuel);

        cout << "Mileage: " << setw(7) << odo.getMileage() << " | Fuel: " << fuel.getGallons() << " gallons" << endl;
    }

    cout << "\nOut of fuel...Stranded." << endl;

    cin.get();
    return 0;
}