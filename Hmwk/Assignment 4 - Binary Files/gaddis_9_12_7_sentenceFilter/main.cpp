/* 
 * File:   main.cpp
 * Author: John Huynh
 * Created on October 24, 2025
 * 
 * Purpose:
 * Write a program that asks the user for two file names. The first file will be opened for
 * input and the second file will be opened for output. (It will be assumed that the first file
 * contains sentences that end with a period.) The program will read the contents of the first
 * file and change all the letters to lowercase except the first letter of each sentence, which
 * should be made uppercase. The revised contents should be stored in the second file.
 */

// Libraries
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Main
int main() {

    string inFileName, outFileName;
    ifstream inFile;
    ofstream outFile;
    char ch;
    bool capitalizeNext = true;

    // Prompt and Input
    cout << "Enter input file name: ";
    cin >> inFileName;
    cout << "Enter output file name: ";
    cin >> outFileName;

    // Validate Input File
    inFile.open(inFileName);
    if (!inFile) {
        cout << "Error opening input file.\n";
        return 1;
    }

    // Validate Output File
    outFile.open(outFileName);
    if (!outFile) {
        cout << "Error opening output file.\n";
        return 1;
    }

    inFile.get(ch);
    while (inFile) {

        // If character is letter, check case
        if (isalpha(ch)) {
            if (capitalizeNext) {
                outFile.put(toupper(ch));
                capitalizeNext = false;
            } else {
                outFile.put(tolower(ch));
            }
        } 

        // If space or special character
        else {
            outFile.put(ch);

            // Check for end of sentence
            if (ch == '.') capitalizeNext = true;
        }

        // Read next character
        inFile.get(ch);
    }

    // Close Files
    inFile.close();
    outFile.close();

    // Exit Stage Right
    cout << "File processing complete.\n";
    return 0;

}