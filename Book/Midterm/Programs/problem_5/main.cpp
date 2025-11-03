/* 
 * File:   main.cpp
 * Author: John Huynh
 * Created on October 30, 2025
 * 
 * Purpose: Identify the largest n for n! using different data types before overflow
 */

// Libraries
#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>

using namespace std;

// Prototypes
void test_integer(const char* label, long double maxVal);
void test_floating(const char* label, long double maxVal);
void print_max(const char* label, unsigned n);
void clearInputBuffer();

// Main Function
int main() {

    cout << "Max n where n! fits in each primitive type\n\n";

    test_integer("signed char", numeric_limits<signed char>::max());
    test_integer("unsigned char", numeric_limits<unsigned char>::max());
    test_integer("short", numeric_limits<short>::max());
    test_integer("unsigned short", numeric_limits<unsigned short>::max());
    test_integer("int", numeric_limits<int>::max());
    test_integer("unsigned int", numeric_limits<unsigned int>::max());
    test_integer("long", numeric_limits<long>::max());
    test_integer("unsigned long", numeric_limits<unsigned long>::max());
    test_integer("long long", numeric_limits<long long>::max());
    test_integer("unsigned long long", numeric_limits<unsigned long long>::max());
    test_floating("float", numeric_limits<float>::max());
    test_floating("double", numeric_limits<double>::max());
    test_floating("long double", numeric_limits<long double>::max());

    // Exit Stage Right
    cout << "\nPress Enter to Exit...";
    cin.get(); 
    return 0;
    
}

// Integers
void test_integer(const char* label, long double maxVal) {
    
    // Unsigned long long will house the biggest factorial
    unsigned long long factorial = 1;

    // Integer
    unsigned n = 1;

    // Stop when (n + 1)! would exceed the type's max
    while (static_cast<long double>(factorial) <= maxVal / (n + 1)) {
        factorial *= (n + 1);
        ++n;
    }

    print_max(label, n);
}

// Decimals
void test_floating(const char* label, long double maxVal) {

    // Long double will house the biggest factorial for decimals
    long double factorial = 1.0L;
    
    // Integer
    unsigned n = 1;

    // Stop when (n + 1)! would exceed the type's max
    while (factorial <= maxVal / (n + 1)) {
        factorial *= (n + 1);
        ++n;
    }

    print_max(label, n);
}

// Print Result
void print_max(const char* label, unsigned n) {
    cout << setw(20) << left << label << " : max n = " << n << "\n";
}
