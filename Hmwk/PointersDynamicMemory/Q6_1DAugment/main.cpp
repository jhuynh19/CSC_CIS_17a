/* 
 * File:  main.cpp
 * Author: John Huynh
 * Created on September 27, 2025
 */

#include <iostream>
using namespace std;

int *getData (int &arraySize); //Read the array
int *augment (const int *intArray, int size); //Augment and copy the original array
void prntAry (const int *intArray, int size); //Print the array

int main () {
    
    int arraySize;
    int *intArray = getData(arraySize);
    int *augArray = augment(intArray, arraySize);

    prntAry(intArray, arraySize);
    
    cout << "\n";
    
    prntAry(augArray, arraySize + 1);

    delete [] intArray;
    delete [] augArray;

    return 0;
}

//Read the array
int *getData (int & arraySize) {
    
    cin >> arraySize;
    
    int *intArray = new int[arraySize];
    
    for (int i = 0; i < arraySize; ++i) {
        
        cin >> intArray[i];
        
    }
    
    return intArray;
    
}

//Augment and copy the original array
int *augment (const int *intArray, int size) {
    
    int *augArray = new int[size + 1];
    
    augArray[0] = 0;
    
    for (int i = 0; i < size; ++i) {
        
        augArray[i + 1] = intArray[i];
        
    }
    
    return augArray;
    
}

//Print the array
void prntAry (const int *intArray, int size) {
    
    for (int i = 0; i < size; ++i) {
        
        cout << intArray[i];
        
        if (i < size - 1) cout << " ";
        
    }
    
}
