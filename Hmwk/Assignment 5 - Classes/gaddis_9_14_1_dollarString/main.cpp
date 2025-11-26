/*
 * File: main.cpp
 * Author: John Huynh
 * Date: November 25, 2025
 * Purpose: Translate Whole Dollars Amounts into English Notation
*/

// Libraries
#include <iostream>
#include <string>

using namespace std;

class Numbers {

    private:
        int number;
        static string lessThan20[20];
        static string tens[10];
        static string hundred;
        static string thousand;

        // Taken from Midterm and changed out variables
        string chunkToText(int n) {
            string out;

            /* Handle Hundreds */
            if (n >= 100) {
                out += lessThan20[n / 100] + " " + hundred;
                n %= 100;
                if (n > 0) out += " "; 
            }

            /* Handle Tens and Ones */
            if (n >= 20) {
                out += tens[n / 10];
                if (n % 10) out += " " + lessThan20[n % 10];
            } else if (n > 0) {
                out += lessThan20[n];
            }

            return out;
        }

    public:
        /* Validate Input */
        Numbers(int n) {
            if (n >= 0 && n <= 9999) {
                number = n;
            } else {
                number = 0;
                cout << "Err: Number must be 0-9999. Defaulting to 0.\n";
            }
        }

        /* Print Result */
        void print() {
            if (number == 0) {
                cout << lessThan20[0] << endl;
                return;
            }

            string result = "";
            int tempNum = number;

            /* Extract Thousands Part */
            int n_thousands = tempNum / 1000;
            int remainder = tempNum % 1000;

            /* Process Thousands Part */
            if (n_thousands > 0) {
                result += lessThan20[n_thousands] + " " + thousand;
                if (remainder > 0) result += " ";
            }

            /* Process Remainder */
            if (remainder > 0) {
                result += chunkToText(remainder);
            }

            cout << result << endl;
        }

};

// Taken from Midterm Checking Program
string Numbers::lessThan20[20] = {
    "Zero",
    "One",
    "Two",
    "Three",
    "Four",
    "Five",
    "Six",
    "Seven",
    "Eight",
    "Nine",
    "Ten",
    "Eleven",
    "Twelve",
    "Thirteen",
    "Fourteen",
    "Fifteen",
    "Sixteen",
    "Seventeen",
    "Eighteen",
    "Nineteen"
};

string Numbers::tens[10] = {
    "", // Zeros
    "", // Tens
    "Twenty",
    "Thirty",
    "Forty",
    "Fifty",
    "Sixty",
    "Seventy",
    "Eighty",
    "Ninety"
};

string Numbers::hundred = "Hundred";
string Numbers::thousand = "Thousand";

// Main Function
int main() {
    int input;

    cout << "Enter a number (0-9999): ";
    cin >> input;

    Numbers number(input);

    cout << "Output: ";
    number.print();

    // Exit Stage Right
    cin.get();
    return 0;
}
