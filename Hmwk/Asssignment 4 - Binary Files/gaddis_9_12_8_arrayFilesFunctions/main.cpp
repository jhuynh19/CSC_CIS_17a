/* 
 * File:   main.cpp
 * Author: John Huynh
 * Created on October 24, 2025
 * 
 * Write a function named arrayToFile. The function should accept three arguments:
 * the name of a file, a pointer to an int array, and the size of the array. The function
 * should open the specified file in binary mode, write the contents of the array to the file,
 * and then close the file.
 * 
 * Write another function named fileToArray. This function should accept three arguments: 
 * the name of a file, a pointer to an int array, and the size of the array. The
 * function should open the specified file in binary mode, read its contents into the array,
 * and then close the file.
 * 
 * Write a complete program that demonstrates these functions by using the arrayToFile
 * function to write an array to a file, and then using the fileToArray function to read
 * the data from the same file. After the data are read from the file into the array, display
 * the array’s contents on the screen. 
 */


// Libraries
#include <iostream>
#include <fstream> 

using namespace std;

// Prototypes
void arrayToFile(const char *fileName, int *arr, int size);
void fileToArray(const char *fileName, int *arr, int size);

// Main
int main() {

    const int SIZE = 5;
    int numbers[SIZE] = {10, 20, 30, 40, 50};
    int results[SIZE];

    // Array to File
    cout << "Writing data to file" << endl;
    arrayToFile("output.txt", numbers, SIZE);

    // File to Array
    cout << "Reading data from file" << endl;
    fileToArray("output.txt", results, SIZE);
    cout << "Contents of the array read from file:" << endl;
    
    for (int i = 0; i < SIZE; i++)
        cout << results[i] << " " << endl;;

    return 0;
}

// Open the specified file in binary mode, read its contents into the array, and then close the file.
void arrayToFile(const char *fileName, int *arr, int size) {

    ofstream outFile(fileName);

    if (!outFile) {

        cerr << "Error opening file for writing.\n";
        return;

    }

    outFile.write(reinterpret_cast<char*>(arr), sizeof(int) * size);

}

// Open the specified file in binary mode, read its contents into the array, and then close the file
void fileToArray(const char *fileName, int *arr, int size) {

    ifstream inFile(fileName);

    if (!inFile) {

        cerr << "Error opening file for reading.\n";
        return;

    }

    inFile.read(reinterpret_cast<char*>(arr), sizeof(int) * size);

}