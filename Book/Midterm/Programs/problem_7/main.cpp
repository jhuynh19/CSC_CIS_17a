/* 
 * File:   main.cpp
 * Author: John Huynh
 * Created on October 30, 2025
 * 
 * Purpose: Create a program to factor integer into prime numbers
 */

// Libraries
#include <iostream>
#include <string>

using namespace std;

// Structures
struct Prime {
    unsigned char power;
    unsigned short prime;
};
struct Primes {
    unsigned short n;
    unsigned char nPrimes;
    Prime* pStrAry;
};

// Prototypes
Primes* factor(int num);
bool isPrime(int);
int power(int, int &);
int nPrimes(int);
bool validatePrimeInput(int &num);
void cleanUp(Primes* p);
void clearInputBuffer();
void prtPrms(const Primes*);
void invalidInput(const string &prompt);


// Main Function
int main() {
    int num;
    validatePrimeInput(num);   

    Primes* pf = factor(num);
    prtPrms(pf);

    // Exit Stage Right
    cout << "\nPress Enter to Exit...";
    clearInputBuffer();
    cin.get();
    cleanUp(pf);
    return 0;
}

// Determine if the number is Prime
bool isPrime(int num) {

    // If it's even, it can only be prime if it's exactly 2
    if (num == 2) return true;

    // If it's even but not 2, then not prime
    if (num % 2 == 0) return false;

    // Test all odd numbers (3-7 fall through aren't checked here)
    for (int odd = 3; odd * odd <= num; odd += 2) {
        if (num % odd == 0) return false;
    }

    // All other numbers are prime
    return true;
}

// What power is this factor and remove from n
int power(int factor, int &num) {
    int exponent = 0;

    // Divide by factor until remainder
    while (num % factor == 0) {
        num /= factor;
        ++exponent;
    }

    return exponent;
}


// Distinct Primes
int nPrimes(int num) {
    int distinctPrimes = 0;

    // Prime factor 2
    if (num % 2 == 0) {
        ++distinctPrimes;

        while (num % 2 == 0) {
            num /= 2;
        }
    }

    // Odd Prime Factors
    for (int odd = 3; odd * odd <= num; odd += 2) {

        if (num % odd == 0) {

            ++distinctPrimes;

            while (num % odd == 0) {
                num /= odd;
            }

        }
    }

    // Fall through for odds 3-7
    if (num > 1) ++distinctPrimes;

    return distinctPrimes;
}

// Prime Factors
Primes* factor(int num) {

    // Create Pointer
    Primes* res = new Primes;

    // Deref pointer
    Primes &r = *res; 

    // Store original number
    r.n = num;

    // Make a copy
    int tmp = num;

    // Get distinct primes
    r.nPrimes = nPrimes(tmp);

    // Create array for prime factors
    r.pStrAry = new Prime[r.nPrimes];

    // Copy num for factoring
    int n = num;
    int i = 0;

    for (int d = 2; d * d <= n && i < r.nPrimes; ++d) {

        if (isPrime(d)) {

            int k = power(d, n);

            // Record if d divides n at least once 
            if (k > 0) {

                r.pStrAry[i].prime = d;    
                r.pStrAry[i].power = k;
                ++i;

            }
        }
    }

    // Leftover is a prime factor itself
    if (n > 1 && i < r.nPrimes) {
        r.pStrAry[i].prime = n;
        r.pStrAry[i].power = 1;
        ++i;
    }

    return res;
}

void prtPrms(const Primes* P) {

    // Deref structure pointer
    const Primes &r = *P;

    // Display original number
    cout << r.n << " = ";

    // Display prime factors
    for (int i = 0; i < r.nPrimes; ++i) {

        cout << r.pStrAry[i].prime << "^" << static_cast<int>(r.pStrAry[i].power);
        if (i + 1 < r.nPrimes) cout << " * ";
    }

    // Move to a new line after printing the entire expression
    cout << '\n';
}

// Input Validation
bool validatePrimeInput(int &num) {
    bool valid = false;

    do {
        cout << "\nInput a number (2 - 65000) to find its prime factors: ";
        cin >> num;

        if (!cin.good()) {
            invalidInput("Invalid input.");
        } else if (num < 2 || num > 65000) {
            invalidInput("Not in valid range (2 - 65000).");
        } else {
            valid = true; 
        }

    } while (!valid);

    return true;
}

// Invalid Inputs
void invalidInput(const string &prompt) {
    cin.clear();
    clearInputBuffer();
    cout << prompt << "\n";
}

// Clear Leftovers
void clearInputBuffer() {
    cin.ignore(10000, '\n');
}

// Delete Data
void cleanUp(Primes* p) { 
    if (p) { 
        delete[] p->pStrAry; 
        delete p; 
    } 
}
