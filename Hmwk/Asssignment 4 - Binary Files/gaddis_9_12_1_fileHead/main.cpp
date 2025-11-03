/* 
 * File:   main.cpp
 * Author: John Huynh
 * Created on October 24, 2025
 * 
 * Purpose:
 * Ask for the name of a file and display the first 10 lines of the file.
 * If the file has fewer than 10 lines, display the entire file and
 * indicate that the whole file has been displayed.
 */

// Libraries
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Main
int main() {
    string fileName;
    ifstream inFile;

    // Get File Name
    cout << "Enter a file name: ";
    getline(cin, fileName);

    // Validate File
    inFile.open(fileName);
    if (!inFile) {
        cout << "Could not open " << fileName << "." << endl;
        return 1;
    }

    string line;
    int lineCount = 0;

    cout << "Displaying the first 10 lines (or full file if shorter):" << endl;

    // Read up to 10 lines of file
    while (getline(inFile, line)) {
        cout << line << endl;
        lineCount++;

        if (lineCount == 10) {
            cout << "\nFirst 10 lines of file have been displayed.\n";
            break;
        }
    }

    // If File Has Less than 10 Lines
    if (inFile.eof() && lineCount < 10)
        cout << "\nEnd of file reached. Entire file has been displayed.\n";

    // Exit Stage Right
    inFile.close();
    return 0;
    
}