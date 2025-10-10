/* 
 * File:  main.cpp
 * Author: John Huynh
 * Created on September 27, 2025
 */

#include <iostream>
using namespace std;

int *getData (int & arraySize); // Return the array size and the array from the inputs
int *sumAry  (const int * intArray, int size); // Return the array with successive sums
void prntAry (const int * intArray, int size); // Print the array

int main () {
    int  arraySize;
    int* intArray  = getData(arraySize);
    int* sumArray  = sumAry(intArray, arraySize);

    prntAry(intArray, arraySize);
    cout << "\n";
    prntAry(sumArray, arraySize);

    delete [] intArray;
    delete [] sumArray;

    return 0;
}

// Input array
int *getData (int & arraySize) {
    
    cin >> arraySize;
    
    int * intArray = new int[arraySize];
    
    for (int i = 0; i < arraySize; ++i) {
        
        cin >> intArray[i];
    }
    
    return intArray;
    
}

// Print the array
int *sumAry (const int *intArray, int size) {
    
    int *sumArray = new int[size];
    int runningSum = 0;
    
    for (int i = 0; i < size; ++i) {
        
        runningSum += intArray[i];
        sumArray[i] = runningSum;
        
    }
    
    return sumArray;
    
}

// Print array
void prntAry (const int * intArray, int size) {
    
    for (int i = 0; i < size; ++i) {
        
        cout << intArray[i];
        
        if (i < size - 1) cout << " ";
        
    }
}
