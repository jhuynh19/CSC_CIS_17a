/* 
 * File: main.cpp
 * Author: John Huynh
 * Created on 12/05/2025
 * Purpose: Absolute Value Template
*/

// Libraries
#include <iostream>
#include <iomanip>

using namespace std;

template <class T>
T absValue(T value) {
    if (value < 0) {
        return -value;
    } else {
        return value;
    }
}

// Main 
int main() {
    int a = -13, b = 19, c = 0;
    float f = -101.1, g = 67.8;

    cout << "Absolute value of |" << a << "|: " << absValue(a) << endl;
    cout << "Absolute value of |" << b << "|: " << absValue(b) << endl;
    cout << "Absolute value of |" << c << "|: " << absValue(c) << endl;

    cout << "Absolute value of |" << f << "|: " << absValue(f) << endl;
    cout << "Absolute value of |" << g << "|: " << absValue(g) << endl;

    // Exit stage right
    cin.get();
    return 0;
}