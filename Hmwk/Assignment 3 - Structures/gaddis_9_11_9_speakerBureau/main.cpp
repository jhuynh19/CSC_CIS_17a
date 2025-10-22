/* 
 * File:   main.cpp
 * Author: John Huynh
 * Created on October 21, 2025
 * Purpose: Speakers Bureau
 */

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct Speaker {
    string name, phone, topic;
    float fee = 0.0;
};

// Prototypes
void clearLine();  
void speakerCreate(Speaker &speaker);
void speakerEdit (Speaker &speaker);
void speakerList(Speaker speakers[], int count);
string checkInput(const string& prompt);
float  validateFee(const string& prompt);


// Main
int main() {

    // Initial speaker count
    int count = 0;

    cout << "Speakers' Bureau\n";
    cout << "How many speaker slots do you want (minimum 10)? ";
    cin >> count;

    // Check if speaker count is more than 10
    while (!cin.good() || count < 10) {

        cin.clear();
        clearLine();
        cout << "Enter an integer >= 10: ";
        cin >> count;

    }

    clearLine();

    Speaker *speakers = new Speaker[count];

    int choice = 0;

    while (choice != 4) {

        // Nav Menu
        cout << "\n1. Enter New Speaker\n"
             << "2. Edit Speaker\n"
             << "3. Display All Speakers\n"
             << "4. Quit\n\n"
             << "Enter choice: ";

        cin >> choice;

        if (!cin.good()) { 
            cin.clear(); 
            clearLine(); 
            choice = 0; 
        }

        // Menu Items
        switch (choice) {

            case 1:
            case 2: {
                int index;
                cout << "Enter index (1 - " << count << "): ";
                cin >> index;
                if (!cin.good()) { cin.clear(); clearLine(); index = -1; }

                if (index >= 1 && index <= count) {
                    clearLine();
                    (choice == 1)
                        ? speakerCreate(speakers[index - 1])
                        : speakerEdit (speakers[index - 1]);
                } else {
                    cout << "Invalid index.\n";
                    clearLine();
                }
                break;
            }

            case 3:
                speakerList(speakers, count);
                break;

            case 4:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice.\n";

        }

    }

    delete[] speakers;
    return 0;
}

// Clear Inputs
void clearLine() {
    cin.ignore(100, '\n');
}

// Create Speaker
void speakerCreate(Speaker &speaker) {
    speaker.name  = checkInput("Enter Name: ");
    speaker.phone = checkInput("Enter Telephone Number: ");
    speaker.topic = checkInput("Enter Speaking Topic: ");
    speaker.fee   = validateFee("Enter Fee Required: ");
}

// Edit Speaker
void speakerEdit(Speaker &speaker) {
    cout << "\nEditing speaker info:\n";
    speakerCreate(speaker);
}

// Display Speakers
void speakerList(Speaker speakers[], int count) {
    cout << "\n=== Speakers List ===\n\n";
    for (int i = 0; i < count; ++i) {
        if (!speakers[i].name.empty()) {
            cout << "\tSpeaker #" << setw(2) << right << (i + 1) << ":\n";
            cout << setw(12) << left << "\tName:"  << speakers[i].name  << '\n';
            cout << setw(12) << left << "\tPhone:" << speakers[i].phone << '\n';
            cout << setw(12) << left << "\tTopic:" << speakers[i].topic << '\n';
            cout << setw(12) << left << "\tFee:"   << "$" << fixed << setprecision(2)
                 << speakers[i].fee << "\n\n";
        }
    }
}

// Checks if input is empty
string checkInput(const string& prompt) {

    string inputStr;
    cout << prompt;
    getline(cin, inputStr);

    while (inputStr.empty()) {

        cout << "This field cannot be empty. " << prompt;
        getline(cin, inputStr);

    }

    return inputStr;
}

// No speaker presentation gives money away
float validateFee(const string& prompt) {

    float fee;

    cout << prompt;
    cin >> fee;

    while (!cin.good() || fee <= 0) {

        cin.clear();
        clearLine();
        cout << "Fee must be a non-negative number. " << prompt;
        cin >> fee;

    }

    clearLine();
    return fee;
}
