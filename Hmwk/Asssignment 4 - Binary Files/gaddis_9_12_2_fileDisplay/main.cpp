/* 
 * File:   main.cpp
 * Author: John Huynh
 * Created on October 24, 2025
 * 
 * Purpose:
 * Ask for a file name and display its contents 24 lines at a time.
 * After each group of 24 lines, wait for the user to press Enter
 * before showing the next 24 lines.
 */

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

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

    // Read and display 24 lines, enter for more
    while (getline(inFile, line)) {
        cout << line << endl;
        ++lineCount;

        if (lineCount % 24 == 0) {
            cout << "Press Enter to continue";
            cin.get();                  
            cout << endl;
        }
    }

    // Exit Stage Right
    inFile.close();
    return 0;
}