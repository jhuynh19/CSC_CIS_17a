/* 
 * File:   main.cpp
 * Author: John Huynh
 * Created on October 24, 2025
 * 
 * Write a program that uses a structure to store the following data on a company division:
 * Division Name (such as East, West, North, or South)
 * Quarter (1, 2, 3, or 4)
 * Quarterly Sales
 * 
 * The user should be asked for the four quarters’ sales figures for the East, West, North,
 * and South divisions. The data for each quarter for each division should be written to
 * a file.
 * 
 * Input Validation: Do not accept negative numbers for any sales figures.
 */

// Libraries
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Structure for division data
struct Division {
    string name;
    float qrt1, qrt2, qrt3, qrt4;
};

// Function prototype
void getSales(Division &div, ofstream &out);

int main() {
    // Create division objects
    Division east  = {"East"};
    Division west  = {"West"};
    Division north = {"North"};
    Division south = {"South"};

    // Open output file
    ofstream outFile("salesReport.txt");
    if (!outFile) {
        cout << "Error opening salesReport.txt" << endl;
        return 1;
    }

    outFile << "Company Quarterly Sales Report\n\n";

    // Collect and record data
    getSales(east, outFile);
    getSales(west, outFile);
    getSales(north, outFile);
    getSales(south, outFile);

    outFile.close();
    cout << "\nThis year's division sales have been written to salesReport.txt" << endl;
    return 0;
}

// Get Sales and Write to File
void getSales(Division &div, ofstream &out) {

    cout << div.name << " Division\n";

    float* quarters[4] = { &div.qrt1, &div.qrt2, &div.qrt3, &div.qrt4 };

    // Ask for and validate sales input
    for (int i = 0; i < 4; i++) {
        cout << "Enter quarter " << (i + 1) << " sales: ";
        cin >> *quarters[i];

        while (*quarters[i] < 0) {
            cout << "There cannot be a negative sales value. Try again. ";
            cin >> *quarters[i];
        }
    }

    // Write to report
    out << div.name << " Division\n";
    for (int i = 0; i < 4; i++) {
        out << "Quarter " << (i + 1) << ": $" << *quarters[i] << endl;
    }
    out << '\n';
}