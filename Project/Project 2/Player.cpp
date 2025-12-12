/* 
 * File:   Player.cpp
 * Author: John Huynh
 * Purpose: Player logic
 */

// Libraries
#include "Player.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <limits>

using namespace std;

// Constructor
Player::Player(string n) : name(n) {
    shipsRemaining = 0;
}

// Destructor
Player::~Player() {
    for (int i = 0; i < fleet.size(); i++) {
        delete fleet[i];
    }
    fleet.clear();
}

// Check if ship fits boundaries of board
bool Player::canPlace(Point p, bool vertical, int length) const {
    int size = myBoard.getSize();

    for (int k = 0; k < length; ++k) {
        int r = p.row + (vertical ? k : 0);
        int c = p.col + (vertical ? 0 : k);

        if (r < 0 || r >= size || c < 0 || c >= size) return false;
        if (myBoard(r, c) != 0) return false;
    }
    return true;
}

// Place ship on board
void Player::applyShipToBoard(Point p, bool vertical, int length, int shipId) {
    for (int k = 0; k < length; ++k) {
        int r = p.row + (vertical ? k : 0);
        int c = p.col + (vertical ? 0 : k);
        myBoard(r, c) = shipId;
    }
}

// Placing ships randomly, meant for auto computer placement
void Player::placeShipsRandomly() {
    int id = 1; 
    int size = myBoard.getSize();

    for (int i = 0; i < fleet.size(); i++) {
        Ship &s = *fleet[i]; 

        bool placed = false;
        while (!placed) {
            int r = rand() % size;
            int c = rand() % size;
            bool vert = rand() % 2;

            if (canPlace(Point(r, c), vert, s.getLength())) {
                applyShipToBoard(Point(r, c), vert, s.getLength(), id);
                placed = true;
            }
        }
        id++;
    }
}

// Shot logic
bool Player::receiveShot(Point p, bool &wasHit, bool &sunk) {
    wasHit = false; 
    sunk = false;

    // Check bounds
    if (p.row < 0 || p.row >= myBoard.getSize() || p.col < 0 || p.col >= myBoard.getSize()) {
        return false;
    }

    // Check ship ID
    int shipId = myBoard(p.row, p.col);
    
    if (shipId > 0) {
        wasHit = true;
        
        Ship &s = *fleet[shipId - 1];
        
        s.takeHit();

        if (s.isSunk()) {
            sunk = true;
            shipsRemaining--;
        }
        return true;
    }
    return false; 
}

// Check win condition
bool Player::hasLost() const {
    return shipsRemaining == 0;
}

// Initialize Fleet
void Player::initFleet(int mode) {
    // Clear out any ships
    for (int i = 0; i < fleet.size(); i++) {
        delete fleet[i];
    }
    fleet.clear();

    // Standard Mode
    if (mode == 1) { 
        fleet.push_back(new Carrier());
        fleet.push_back(new Battleship());
        fleet.push_back(new Cruiser());
        fleet.push_back(new Submarine());
        fleet.push_back(new Destroyer());
    } 

    // Rapid Mode
    else { 
        fleet.push_back(new Cruiser());
        fleet.push_back(new Submarine());
        fleet.push_back(new Destroyer());
    }
    
    shipsRemaining = fleet.size();
}

// Print Boards to Console
void Player::printBoards() const {
    cout << "   Your Board             Enemy Board\n";
    cout << "   ----------             -----------\n";
    
    int size = myBoard.getSize();
    for (int r = 0; r < size; ++r) {

        // Left Side is player board
        cout << r << " |";
        for (int c = 0; c < size; ++c) {
            int id = myBoard(r, c);
            char sym = '.';
            
            if (id > 0) {
                Ship &s = *fleet[id - 1];
                sym = s.getSymbol(); 
            }
            cout << " " << sym;
        }
        
        cout << " |   "; 

        // Right Side is computer's board
        cout << r << " |";
        for (int c = 0; c < size; ++c) {
            char mark = enemyBoard(r, c);
            if (mark == 0) mark = '.';
            cout << " " << mark;
        }
        cout << " |\n";
    }
}

void HumanPlayer::drawPlacementView(Point cursor, bool vertical, Ship* s) const {
    // Clear screen
    cout << string(50, '\n');
    
    cout << "Place: " << s->getName() << " (Size " << s->getLength() << ", " 
         << (vertical ? "Vertical" : "Horizontal") << ")\n";
    cout << "Controls: W/A/S/D move | R rotate | P place\n";

    // Header
    cout << "    ";
    for (int col = 0; col < getBoardSize(); ++col) cout << (char)('A' + col) << " ";
    cout << "\n    " << string(getBoardSize() * 2, '-') << "\n";

    int size = getBoardSize();
    for (int r = 0; r < size; ++r) {
        cout << setw(2) << r << " |";
        
        for (int c = 0; c < size; ++c) {
            bool isGhost = false;
            
            for (int k = 0; k < s->getLength(); ++k) {
                int ghostR = cursor.row + (vertical ? k : 0);
                int ghostC = cursor.col + (vertical ? 0 : k);
                
                if (r == ghostR && c == ghostC) {
                    isGhost = true;
                    break;
                }
            }

            // Determine what to print
            char sym = '.';
            int shipId = myBoard(r, c); 
            
            if (isGhost) {
                sym = 'X'; 
            } else if (shipId > 0) {
                sym = fleet[shipId-1]->getSymbol(); 
            }
            
            cout << " " << sym;
        }
        cout << "\n";
    }
}

void HumanPlayer::placeShips() {
    Point cursor(0, 0);
    bool vertical = false;
    int shipId = 1;

    for (int i = 0; i < fleet.size(); i++) {
        Ship &s = *fleet[i]; 
        bool placed = false;
        
        while (!placed) {

            drawPlacementView(cursor, vertical, &s);
            cout << "Command: ";

            char cmd;
            cin >> cmd;
            cmd = toupper(cmd);

            int size = myBoard.getSize();

            switch (cmd) {
                case 'W': if (cursor.row > 0) cursor.row--; break;
                case 'S': if (cursor.row < size - 1) cursor.row++; break;
                case 'A': if (cursor.col > 0) cursor.col--; break;
                case 'D': if (cursor.col < size - 1) cursor.col++; break;
                case 'R': vertical = !vertical; break;
                case 'P': 
                    if (canPlace(cursor, vertical, s.getLength())) {
                        applyShipToBoard(cursor, vertical, s.getLength(), shipId);
                        placed = true;
                        shipId++;
                    } else {
                        cout << "Invalid Position!\n";
                        cin.ignore(); cin.get(); 
                    }
                    break;
            }
        }
    }
}

Point HumanPlayer::makeMove() {
    string input;
    int r, c;
    
    while (true) {
        cout << getName() << ", enter target (e.g. A5): ";
        cin >> input;
        
        if (sscanf(input.c_str(), "%c%d", &colChar, &rowNum) == 2) {
            
            colChar = toupper(colChar);

            // Check if column letter is valid
            if (colChar >= 'A' && colChar < 'A' + getBoardSize()) {
                c = colChar - 'A';
                r = rowNum;

                // Check if row number is valid 
                if (r >= 0 && r < getBoardSize()) {
                    
                    // Check if we already shot there
                    if (enemyBoard(r, c) == 0) { 
                        return Point(r, c);
                    } else {
                        cout << "Already shot there.\n";
                    }
                }
            }
        }
        cout << "Invalid coordinate. Try again.\n";
    }
}

ComputerPlayer::ComputerPlayer() : Player("Computer") {
    huntMode = true;
}

void ComputerPlayer::placeShips() {
    placeShipsRandomly();
}

void ComputerPlayer::addAdjacentTargets(Point p) {
    potentialTargets.push_back(Point(p.row - 1, p.col));
    potentialTargets.push_back(Point(p.row + 1, p.col));
    potentialTargets.push_back(Point(p.row, p.col - 1));
    potentialTargets.push_back(Point(p.row, p.col + 1));
}

Point ComputerPlayer::makeMove() {
    Point target;
    bool valid = false;
    int size = getBoardSize();

    while (!valid) {
        if (potentialTargets.empty()) huntMode = true;

        if (huntMode) {
            target.row = rand() % size;
            target.col = rand() % size;
        } else {
            target = potentialTargets.back();
            potentialTargets.pop_back();
        }

        if (target.row >= 0 && target.row < size && target.col >= 0 && target.col < size) {
            if (enemyBoard(target.row, target.col) == 0) valid = true;
        }
    }
    return target;
}