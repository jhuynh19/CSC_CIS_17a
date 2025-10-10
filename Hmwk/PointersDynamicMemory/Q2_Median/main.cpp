/* 
 * File:  main.cpp
 * Author: John Huynh
 * Created on September 25, 2025
 */

#include <iostream>
#include <iomanip>
using namespace std;

// Prototypes
int *getData (int &arraySize); // Return the array size and the array
void prntDat (int *intArray, int size); // Print the integer array
float *median (int *intArray, int size); // Fill the median Array with the Float array size, the median, and the integer array data
void prntMed (float *medianArray); // Print the median Array

// Selection Sort for Calculation
void selSort (int *intArray, int size) {
    
    for (int left = 0; left < size - 1; ++left) {
        
        int minIdx = left;
        
        for (int scan = left + 1; scan < size; ++scan) {
            
            if (intArray[scan] < intArray[minIdx]) minIdx = scan;
            
        }
        if (minIdx != left) {
            
            int tmp = intArray[left];
            
            intArray[left] = intArray[minIdx];
            
            intArray[minIdx] = tmp;
            
        }
    }
}

// Main
int main () {
    int arraySize;
    int *intArray = getData(arraySize);

    prntDat(intArray, arraySize);

    float *medianArr = median(intArray, arraySize);

    prntMed(medianArr);

    delete [] intArray;
    delete [] medianArr;

    return 0;
}

// Return dynamically allocated int array
int *getData (int & arraySize) {
    
    cin >> arraySize;

    int *intArray = new int[arraySize];
    
    for (int i = 0; i < arraySize; ++i) {
        
        cin >> intArray[i];
        
    }
    
    return intArray;
    
}

// Print the integer array
void prntDat (int *intArray, int size) {
    
    for (int i = 0; i < size; ++i) {
        
        cout << intArray[i];
        
        if (i < size - 1) cout << " ";
        
    }
    
    cout << "\n";
}

// Build the float median array
float *median (int *intArray, int size) {
    
    // Create Copy
    int *sortedCopy = new int[size];
    
    for (int i = 0; i < size; ++i) {
        
        sortedCopy[i] = intArray[i];
        
    }
    
    selSort(sortedCopy, size);

    float medianValue = (size % 2 == 1)
        ? static_cast<float>(sortedCopy[size / 2])
        : (static_cast<float>(sortedCopy[size / 2 - 1]) +
           static_cast<float>(sortedCopy[size / 2])) / 2.0f;

    delete [] sortedCopy;

    float *medianArray = new float[size + 2];
    
    medianArray[0] = static_cast<float>(size + 2); // store float array size
    
    medianArray[1] = medianValue;                  // store median
    
    for (int i = 0; i < size; ++i) {
        
        medianArray[i + 2] = static_cast<float>(intArray[i]);
        
    }
    
    return medianArray;
}

// Print the float array
void prntMed (float *medianArray) {
    
    int floatArraySize = static_cast<int>(medianArray[0]);

    // First element as integer
    cout << floatArraySize;

    // Remaining elements with 2 decimals
    cout << fixed << setprecision(2);
    
    for (int i = 1; i < floatArraySize; ++i) {
        
        cout << " " << medianArray[i];
        
    }
}
