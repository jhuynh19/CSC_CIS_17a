/* 
 * File: Game.cpp
 * Author: John Huynh
 * Purpose: Game Controller
 */

#include "Game.h"
#include <iostream>
#include <string>

using namespace std;

// Initialize Static Member
int Game::gamesPlayed = 0;

Game::Game() {
    player = NULL;
    computer = NULL;
}

// Clean up memory when game ends
Game::~Game() {
    delete player;
    delete computer;
}

void Game::setup() {

    // Select Mode 
    int choice;

    cout << "\nChoose game mode:\n";
    cout << "1. Standard\n";
    cout << "2. Rapid\n";
    cout << "Select 1 or 2: ";
    cin >> choice;
    
    // Input Validation
    while (choice != 1 && choice != 2) {
        cout << "Invalid input. Please choose a game mode: ";
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> choice;
    }

    // Create Players
    player = new HumanPlayer("Player");
    computer = new ComputerPlayer(); 

    // 3. Initialize Fleets
    Player &p = *player;
    Player &c = *computer;
    p.initFleet(choice);
    c.initFleet(choice);
}
