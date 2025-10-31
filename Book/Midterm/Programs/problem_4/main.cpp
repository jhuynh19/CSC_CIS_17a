/* 
 * File:   main.cpp
 * Author: John Huynh
 * Created on October 29, 2025
 * 
 * Purpose: Create an encryption program for 4-digit integers
 */


// Libraries
#include <iostream>
#include <string>

using namespace std;

// Prototypes
string encrypt(string num);
string decrypt(string num);


int main() {
    string num;
    cout << "Enter a 4-digit number (0–7 only): ";
    cin >> num;

    string enc = encrypt(num);
    cout << "Encrypted: " << enc << endl;

    if (enc.rfind("Error", 0) != 0) { // If no error
        cout << "Decrypted back: " << decrypt(enc) << endl;
    }

    return 0;
}


string encrypt(string num) {
    // Validate input
    if (num.size() != 4) return "Error: must be 4 digits.";
    for (char c : num)
        if (c < '0' || c > '7') return "Error: digits must be 0–7 only.";

    // Convert and encrypt
    for (char &c : num)
        c = ((c - '0' + 3) % 8) + '0';

    // Swap 1st↔3rd, 2nd↔4th
    swap(num[0], num[2]);
    swap(num[1], num[3]);

    return num;
}

string decrypt(string num) {
    if (num.size() != 4) return "Error: must be 4 digits.";
    for (char c : num)
        if (c < '0' || c > '7') return "Error: digits must be 0–7 only.";

    // Swap back
    swap(num[0], num[2]);
    swap(num[1], num[3]);

    // Reverse encryption
    for (char &c : num)
        c = ((c - '0' + 8 - 3) % 8) + '0';

    return num;
}