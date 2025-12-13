/* 
 * File: Game.cpp
 * Author: John Huynh
 * Purpose: Game Controller
 */

#include "Game.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Initialize Static Member
int Game::gamesPlayed = 0;

Game::Game() {
    player = NULL;
    computer = NULL;

    loadStats();
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

    // Initialize Fleets
    Player &p = *player;
    Player &c = *computer;

    if (choice == 2) {
        p.setBoardSize(5);
        c.setBoardSize(5);
    }

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
    bool playerWon = false;
    
    while (!gameOver) {
        // Player Turn

        cout << string(50, '\n'); 
        p.printBoards();       

        // Get Valid Move from Player
        Point target = p.makeMove();
        
        // Fire at Computer
        if (c.receiveShot(target, hit, sunk)) {
            cout << "HIT!";
            if (sunk) cout << " You sunk a ship!";
            p.markShot(target, true);
        } else {
            cout << "Miss.";
            p.markShot(target, false);
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
            playerWon = true;
            break; 
        }

        // Computer's Turn
        
        Point cpuTarget = c.makeMove();
        
        // Fire at Player
        if (p.receiveShot(cpuTarget, hit, sunk)) {
            cout << "Computer fires " << cpuTarget << " -> HIT!\n";
            if (sunk) cout << "Your ship was sunk!\n";
            c.markShot(cpuTarget, true);

            ComputerPlayer* cpuPtr = dynamic_cast<ComputerPlayer*>(computer);
            
            if (cpuPtr) {
                ComputerPlayer &cpu = *cpuPtr;
                cpu.addAdjacentTargets(cpuTarget);
            }
            
        } else {
            cout << "Computer fires " << cpuTarget << " -> Miss.\n";
            c.markShot(cpuTarget, false);
        }
        
        // Check Loss
        if (p.hasLost()) {
            cout << "\nYou Lose!\n";
            gameOver = true;
            playerWon = false;
        }
        
        // Pause between turns
        if (!gameOver) {
            cout << "Press Enter for next turn...";
            cin.ignore(); 
            cin.get();
        }
    }

    // Update Stats
    currentStats.totalGames++;

    if (playerWon) {
        currentStats.userWins++;
    }

    saveStats();

    gamesPlayed++;
}

void Game::loadStats() {
    std::ifstream in("stats.dat", std::ios::binary);
    
    // If file exists
    if (in) {
        in.read(reinterpret_cast<char*>(&currentStats), sizeof(Stats));
    } else {
        currentStats.totalGames = 0;
        currentStats.userWins = 0;
    }
}

void Game::saveStats() {
    std::ofstream out("stats.dat", std::ios::binary);
    if (out) {
        out.write(reinterpret_cast<const char*>(&currentStats), sizeof(Stats));
    }
}

void Game::displayStats() const {
    cout << "\nPlayer Statistics\n";
    cout << left << setw(12) << "Total Games:" << currentStats.totalGames << "\n";
    cout << left << setw(12) << "User Wins:" << currentStats.userWins << "\n";
    
    if (currentStats.totalGames > 0) {
        // Calculate percentage
        int pct = (currentStats.userWins * 100) / currentStats.totalGames;
        cout << left << setw(10) << "Win Rate:" << pct << "%\n";
    } else {
        cout << left << setw(10) << "Win Rate:" << "0%\n";
    }
}