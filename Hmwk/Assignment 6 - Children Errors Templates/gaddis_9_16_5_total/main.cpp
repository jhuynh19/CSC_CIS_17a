/* 
 * File: main.cpp
 * Author: John Huynh
 * Created on 12/05/2025
 * Purpose: Keep running total of values
*/

// Libraries
#include <iostream>
#include <iomanip>

using namespace std;

// Templates
template <class T>
T total(int count) {
    T sum = T();
    T userVal;

    cout << "\nEnter " << count << " values of type [" << typeid(T).name() << "]:" << endl;

    for (int i = 0; i < count; ++i) {
        cout << "Enter value #" << (i + 1) << ": ";
        cin >> userVal;
        sum += userVal;
    }
    
    return sum;
}

// Globals
const int NUM_VALUES = 3;

// Main
int main() {
    
    int intTotal;
    float floatTotal;

    // Integer sum output
    intTotal = total<int>(NUM_VALUES);
    cout << "Total of integers: " << intTotal << endl;

    // Float sum output
    floatTotal = total<float>(NUM_VALUES);
    cout << fixed << setprecision(2);
    cout << "Total of floats: " << floatTotal << endl;

    // Exit stage right
    cin.get();
    return 0;
}