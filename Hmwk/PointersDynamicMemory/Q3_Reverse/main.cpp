/* 
 * File:  main.cpp
 * Author: John Huynh
 * Created on September 27, 2025
 */

#include <iostream>
using namespace std;

int *getData (int & arraySize); // Fill the array
int *sort (const int * intArray, int size); // Sort smallest to largest
int *reverse (const int * intArray, int size); // Reverse sorted array
void  prntDat (const int * intArray, int size); // Print array

// Main 
int main () {
    
    int  arraySize;
    int* intArray    = getData(arraySize);

    int* sortedArray = sort(intArray, arraySize);
    int* revArray    = reverse(sortedArray, arraySize);

    prntDat(sortedArray, arraySize);  
    cout << "\n";
    prntDat(revArray, arraySize);

    delete [] intArray;
    delete [] sortedArray;
    delete [] revArray;

    return 0;
}

// Fill the array
int *getData (int & arraySize) {

    cin >> arraySize;

    int *intArray = new int[arraySize];

    for (int i = 0; i < arraySize; ++i) {
        cin >> intArray[i];
    }
    
    return intArray;
}

// Sort array smallest to largest
int *sort (const int * intArray, int size) {

    int *sorted = new int[size];

    for (int i = 0; i < size; ++i) sorted[i] = intArray[i];

    for (int i = 0; i < size - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < size; ++j) {
            if (sorted[j] < sorted[minIdx]) minIdx = j;
        }
        if (minIdx != i) {
            int tmp        = sorted[i];
            sorted[i]      = sorted[minIdx];
            sorted[minIdx] = tmp;
        }
    }

    return sorted;
}

// Reverse sorted array  
int *reverse (const int * intArray, int size) {

    int *rev = new int[size];

    for (int i = 0; i < size; ++i) {
        rev[i] = intArray[size - 1 - i];
    }

    return rev;
}

// Print array 
void prntDat (const int * intArray, int size) {

    for (int i = 0; i < size; ++i) {
        cout << intArray[i];
        if (i < size - 1) cout << " ";
    }

}
