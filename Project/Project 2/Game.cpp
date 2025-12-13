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

void Game::run() {
    int choice = 0;
    
    do {
        cout << "\nBattleship\n";
        cout << "1. Play Battleship\n";
        cout << "2. View Statistics\n";
        cout << "3. View Game History\n";
        cout << "4. Quit\n";
        cout << "Select an option: ";
        cin >> choice;

        // Input Validation
        if (cin.fail()) {
            cin.clear(); cin.ignore(10000, '\n');
            choice = 0;
        }

        switch (choice) {
            case 1:
                setup(); 
                play();  
                break;
            case 2:
                displayStats();
                break;
            case 3:
                displayHistory();
                break;
            case 4:
                cout << "Thanks for playing!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
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

        // Handle game quit
        if (target.isQuit()) {
            cout << "\nYou forfeited the match!\n";
            gameOver = true;
            playerWon = false;
            break; 
        }
        
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
    saveGameRecord(playerWon);

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
    cout << left << setw(20) << "Total Games:" << currentStats.totalGames << "\n";
    cout << left << setw(20) << "User Wins:" << currentStats.userWins << "\n";
    
    if (currentStats.totalGames > 0) {
        // Calculate percentage
        int pct = (currentStats.userWins * 100) / currentStats.totalGames;
        cout << left << setw(20) << "Win Rate:" << pct << "%\n";
    } else {
        cout << left << setw(20) << "Win Rate:" << "0%\n";
    }
}

void Game::saveGameRecord(bool playerWon) {
    GameRecord rec;
    rec.gameId = currentStats.totalGames;
    rec.playerWon = playerWon;

    for(int r=0; r<10; r++) {
        for(int c=0; c<10; c++) { 
            rec.playerShots[r][c] = '.'; 
            rec.cpuShots[r][c] = '.'; 
        }
    }
    
    int size = player->myBoard.getSize();

    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            char pShot = player->enemyBoard(r, c);
            if (pShot != 0) rec.playerShots[r][c] = pShot;

            char cShot = player->incomingShots(r, c);
            if (cShot != 0) rec.cpuShots[r][c] = cShot;
        }
    }

    // Append to binary file
    ofstream out("history.dat", ios::binary | ios::app);
    if (out) {
        out.write(reinterpret_cast<const char*>(&rec), sizeof(GameRecord));
    }
}

void Game::displayHistory() const {
    ifstream in("history.dat", ios::binary);
    
    if (!in) {
        cout << "\nNo game history found.\n";
        return;
    }

    GameRecord rec;
    cout << "\nGame History\n";
    cout << "ID\tResult\n";
    cout << "--\t------\n";

    while (in.read(reinterpret_cast<char*>(&rec), sizeof(GameRecord))) {
        cout << "\n========================================\n";
        cout << " Game #" << rec.gameId << " | Result: " 
             << (rec.playerWon ? "PLAYER WON" : "COMPUTER WON") << "\n";
        cout << "========================================\n";

        cout << "   Enemy Board            Your Board\n";
        cout << "   -----------            ----------\n";
        
        for (int r = 0; r < 10; ++r) {
            
            cout << r << " |";
            for (int c = 0; c < 10; ++c) {
                char mark = rec.playerShots[r][c];
                cout << " " << (mark == 0 ? '.' : mark);
            }
            cout << " |   ";

            cout << r << " |";
            for (int c = 0; c < 10; ++c) {
                char mark = rec.cpuShots[r][c];
                cout << " " << (mark == 0 ? '.' : mark);
            }
            cout << " |\n";
        }
    }
}