/* 
 * File: main.cpp
 * Author: John Huynh
 * Created on 12/05/2025
 * Purpose: Minimum/Maximum Function Templates
*/

// Libraries
#include <iostream>
#include <string>

using namespace std;

// Templates
template <class T1, class T2>
T1 minimum(T1 value1, T2 value2) {
    if (value1 < value2) {
        return value1;
    } else {
        return value2;
    }
}

template <class T1, class T2>
T1 maximum(T1 value1, T2 value2) {
    if (value1 > value2) {
        return value1;
    } else {
        return value2;
    }
}

// Main
int main() {
    int a = 13, b = 19;
    float f = 101.1, g = 67.8;
    string x = "Valve", y = "Epic";
    char s = '+', t = '%';

    cout << "Values: " << a << ", " << b << endl;
    cout << "Minimum: " << minimum(a, b) << endl;
    cout << "Maximum: " << maximum(a, b) << endl;
    
    cout << "\n";

    cout << "Values: " << f << ", " << g << endl;
    cout << "Minimum: " << minimum(f, g) << endl;
    cout << "Maximum: " << maximum(f, g) << endl;
    
    cout << "\n";

    cout << "Values: " << x << ", " << y << endl;
    cout << "Minimum: " << minimum(x, y) << endl;
    cout << "Maximum: " << maximum(x, y) << endl;
    
    cout << "\n";
    
    cout << "Values: " << s << ", " << t << endl;
    cout << "Minimum: " << minimum(s, t) << endl;
    cout << "Maximum: " << maximum(s, t) << endl;

    // Exit stage right
    cin.get();
    return 0;
}