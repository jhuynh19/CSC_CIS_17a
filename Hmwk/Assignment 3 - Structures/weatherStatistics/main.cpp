/* 
 * File:   main.cpp
 * Author: John Huynh
 * Created on October 19, 2025
 * Purpose: Weather Statistics (judge format, no prompts)
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;

struct Weather {
    string month;
    float rain, low, high, avg;   
};

int main() {

    const int MONTHS = 12;
    Weather year[MONTHS];

    // Read in inputs
    for (int i = 0; i < MONTHS; ++i) {

        cin >> year[i].month >> year[i].rain >> year[i].low >> year[i].high;
        
        // Calculate Average Temp for the Month
        year[i].avg = (year[i].low + year[i].high) / 2;
    }

    // Calculate Total Rain, Year Average Temp, Lowest and Highest Temps
    string lowestMonth, highestMonth;
    float totalRain = 0, lowTemp = 140, highTemp = -100, avgTemp = 0;

    for (int i = 0; i < MONTHS; ++i) {

        totalRain += year[i].rain;
        avgTemp += year[i].avg;

        if (year[i].low < lowTemp) { lowTemp = year[i].low; lowestMonth = year[i].month; }
        if (year[i].high > highTemp) { highTemp = year[i].high; highestMonth = year[i].month; }

    }

    // Averages
    float avgRain = totalRain / MONTHS;
    float avgYear = avgTemp / MONTHS;       

    // Weather Report
    cout << fixed << setprecision(1);
    cout << "Average Rainfall " << avgRain << " inches/month\n";
    cout << setprecision(0) << fixed;
    cout << "Lowest  Temperature "  << lowestMonth << "  " << lowTemp << " Degrees Fahrenheit\n";
    cout << "Highest Temperature " << highestMonth << "  " << highTemp << " Degrees Fahrenheit\n";
    cout << "Average Temperature for the year " << avgYear << " Degrees Fahrenheit\n";

    return 0;
}
