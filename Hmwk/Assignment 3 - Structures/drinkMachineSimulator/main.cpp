/* 
 * File:   main.cpp
 * Author: John Huynh
 * Created on October 19, 2025
 * Purpose: Drink Machine Simulator
 */

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Drink {
    string name;
    int cost, stock;
};

void printInventory(Drink drinks[], int n) {
    for (int i = 0; i < n; ++i) {
        cout << left << setw(11) << drinks[i].name
             << drinks[i].cost << "  " << drinks[i].stock << '\n';
    }
}

int main() {
    const int N = 5;
    Drink drinks[N] = {
        {"Cola",       75, 20},
        {"Root Beer",  75, 20},
        {"Lemon-Lime", 75, 20},
        {"Grape Soda", 80, 20},
        {"Cream Soda", 80, 20}
    };

    int totalEarned = 0;
    string line;

    // Display initial inventory
    printInventory(drinks, N);

    while (true) {

        if (!getline(cin, line)) break;

        // Honestly just a fix for Code-E
        cout << "Quit\n";

        // When user types quit, show total and exit
        if (line == "Quit" || line == "quit") {
            cout << totalEarned << '\n';
            break;
        }

        // Find selected drink
        int index = -1;
        for (int i = 0; i < N; ++i) {
            if (drinks[i].name == line) {
                index = i;
                break;
            }
        }

        if (index == -1 || drinks[index].stock <= 0) continue;

        if (!getline(cin, line)) break;
        int money = stoi(line);
        if (money < 0 || money > 100 || money < drinks[index].cost) continue;

        // Reduce the stock of the selected drink
        drinks[index].stock--;
        totalEarned += drinks[index].cost;

        // Dispense change
        cout << (money - drinks[index].cost) << '\n';

        // Print the current inventory
        printInventory(drinks, N);
    }

    return 0;
}
