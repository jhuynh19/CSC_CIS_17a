/* 
 * File: main.cpp
 * Author: John Huynh
 * Created on September 9th, 2025, 10:00 PM
 * Purpose: Write a program that maintains three arrays and initializes the highest temperature, lowest temperature, and humidity in the three arrays, for each day of the first 10 days of a month.
 * The program should then create a weather report that includes the following information:
    > Highest temperature and lowest temperature.
    > Diurnal variation in each day.
    > Humidity of each day and whether it is greater or less than the average humidity.
 * Display the maximum temperature, minimum temperature, and overall variation in temperature in the duration.
 */

//System Libraries
#include <iostream>
#include <iomanip>

using namespace std;

const int daysRec = 10; // Days Collected

// Prototypes
void wthrRpt(int lows[], int highs[], int humid[], int days);

// Main Function
int main() {
    int hTmp[daysRec]; // High Temp
    int lTmp[daysRec]; // Low Temp
    int hmdty[daysRec]; // Humidity

    cout << "Enter the high, low, and humidity for " << daysRec << " days:\n\n";

    for (int i = 0; i < daysRec; i++) {
        cout << "Day " << (i + 1) << ":\n";
        cout << "High temperature:\t";
        cin >> hTmp[i];
        cout << "Low temperature:\t";
        cin >> lTmp[i];
        cout << "Humidity (%):\t";
        cin >> hmdty[i];
        cout << endl;
    }

    wthrRpt(lTmp, hTmp, hmdty, daysRec);

    return 0;
}

void wthrRpt(int lows[], int highs[], int humid[], int days) {
    
    // Calculate Average Humidity
    float humTot, avgHum;

    for (int i = 0; i < days; i++) {
        humTot += humid[i];
    }

    avgHum = (humTot) / days;

    // Record highest/lowest days
    int overallMinDay, overallMaxDay;
    int overallMax = highs[0]; 
    int overallMin = lows[0];

    // Set up Report
    cout << "\nWeather Report\n\n";
    cout << left << setw(6) << "Day" 
        << setw(8) << "Low" 
        << setw(8)  << "High" 
        << setw(10) << "Variation"
        << setw(12) << "Humidity" 
        << "vs Avg\n";

    for (int i = 0; i < days; i++) {
        int rng = highs[i] - lows[i]; // Change in temperature
        char cmp; // Check if higher or lower
        if (humid[i] > avgHum) {
            cmp = '>';
        } else if (humid[i] < avgHum) {
            cmp = '<';
        } else {
            cmp = '=';
        }

        cout << left << setw(6) << (i + 1) 
            << setw(8)  << lows[i]
            << setw(8)  << highs[i]
            << setw(10) << rng
            << setw(12) << humid[i]
            << " " << cmp << "\n";

        // Check against record temps, update if new record
        if (highs[i] > overallMax) { overallMax = highs[i]; overallMaxDay = i + 1; }
        if (lows[i] < overallMin) { overallMin = lows[i]; overallMinDay = i + 1; }
    }

    int overallVariation = overallMax - overallMin;

    cout << "\nMaximum temperature: " << overallMax << " (Day " << overallMaxDay << ")\n";
    cout << "Minimum temperature: " << overallMin << " (Day " << overallMinDay << ")\n";
    cout << "Temperature Variation  : " << overallVariation << " degrees\n";
}