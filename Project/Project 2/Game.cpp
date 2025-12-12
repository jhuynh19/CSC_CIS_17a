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

void Game::play() {
    Player &p = *player;
    Player &c = *computer;

    p.placeShips();
    c.placeShips(); 

    cout << "\nAll ships placed! Battle commencing...\n";
    
    // Main Game Loop
    bool gameOver = false;
    bool hit = false;
    bool sunk = false;
    
    while (!gameOver) {
        // Player Turn

        cout << string(2, '\n'); 
        p.printBoards();       

        // Get Valid Move from Player
        Point target = p.makeMove();
        
        // Fire at Computer
        if (c.receiveShot(target, hit, sunk)) {
            cout << "HIT!";
            if (sunk) cout << " You sunk a ship!";
        } else {
            cout << "Miss.";
        }
        cout << "\n";
        
        if (sunk) {
             cout << "Press Enter...";
             cin.ignore(); cin.get();
        }

        // Check Win
        if (c.hasLost()) {
            cout << "\nYou win!\n";
            gameOver = true;
            break; 
        }

        // Computer's Turn
        
        Point cpuTarget = c.makeMove();
        
        // Fire at Player
        if (p.receiveShot(cpuTarget, hit, sunk)) {
            cout << "Computer fires " << cpuTarget << " -> HIT!\n";
            if (sunk) cout << "Your ship was sunk!\n";
            
            ComputerPlayer* cpuPtr = dynamic_cast<ComputerPlayer*>(computer);
            
            if (cpuPtr) {
                ComputerPlayer &cpu = *cpuPtr;
                cpu.addAdjacentTargets(cpuTarget);
            }
            
        } else {
            cout << "Computer fires " << cpuTarget << " -> Miss.\n";
        }
        
        // Check Loss
        if (p.hasLost()) {
            cout << "\nYou Lose!\n";
            gameOver = true;
        }
        
        // Pause between turns
        if (!gameOver) {
            cout << "Press Enter for next turn...";
            cin.ignore(); cin.get();
        }
    }

    // Update Stats
    gamesPlayed++;
}