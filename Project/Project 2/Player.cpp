/* 
 * File:   Player.cpp
 * Author: John Huynh
 * Purpose: Human player and computer logic
 */

// Libraries
#include "Player.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <string>

using namespace std;

/**
 * @brief Constructor. Initializes player name and ship count.
 * @param n Name of the player.
 */
Player::Player(string n) : name(n) {
    shipsRemaining = 0;
}

/**
 * @brief Destructor. Cleans up dynamically allocated ships.
 */
Player::~Player() {
    for (int i = 0; i < fleet.size(); i++) {
        delete fleet[i];
    }
    fleet.clear();
}

/**
 * @brief Checks if a ship can be placed at a specific location.
 * Verifies boundaries and overlap with existing ships.
 * @param p Starting coordinate.
 * @param vertical Orientation flag.
 * @param length Size of the ship.
 * @return true if valid, false otherwise.
 */
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

/**
 * @brief Writes the ship's ID to the board grid.
 * @param p Starting coordinate.
 * @param vertical Orientation flag.
 * @param length Size of the ship.
 * @param shipId Unique ID of the ship.
 */
void Player::applyShipToBoard(Point p, bool vertical, int length, int shipId) {
    for (int k = 0; k < length; ++k) {
        int r = p.row + (vertical ? k : 0);
        int c = p.col + (vertical ? 0 : k);
        myBoard(r, c) = shipId;
    }
}

/**
 * @brief Places all ships in the fleet randomly.
 * Used by ComputerPlayer and potentially for auto-setup.
 */
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

/**
 * @brief Processes a shot fired at this player.
 * Updates the board, ship health, and win condition.
 * @param p Coordinate of the shot.
 * @param wasHit [out] True if a ship was hit.
 * @param sunk [out] True if a ship sank.
 * @param sunkName [out] Name of the sunk ship.
 * @return true if shot was valid, false if invalid.
 */
bool Player::receiveShot(Point p, bool &wasHit, bool &sunk, string &sunkName) {
    wasHit = false; 
    sunk = false;
    sunkName = "";

    // Check Bounds
    if (p.row < 0 || p.row >= myBoard.getSize() || p.col < 0 || p.col >= myBoard.getSize()) {
        return false;
    }

    // Check Ship ID
    int shipId = myBoard(p.row, p.col);
    
    if (shipId > 0) {
        wasHit = true;
        
        // Mark Hit
        incomingShots(p.row, p.col) = 'X';
        Ship &s = *fleet[shipId - 1];
        
        s.takeHit();

        if (s.isSunk()) {
            sunk = true;
            sunkName = s.getName();
            shipsRemaining--;
        }
        return true;
    }
    
    // Mark Miss
    incomingShots(p.row, p.col) = 'O'; 
    
    return false;
}

/**
 * @brief Checks if the player has lost (0 ships remaining).
 * @return true if lost.
 */
bool Player::hasLost() const {
    return shipsRemaining == 0;
}

/**
 * @brief Initializes the fleet based on game mode.
 * @param mode 1 = Standard (5 ships), 2 = Rapid (3 ships).
 */
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

/**
 * @brief Displays both Player and Enemy boards side-by-side.
 */
void Player::printBoards() const {
    
    int size = myBoard.getSize();

    // Header
    cout << string(3, ' ') << "Your Board" << string(size * 2 - 8, ' ') << string(3, ' ') << "Enemy Board\n";
    cout << string(3, ' ');
    for (int c = 0; c < size; ++c) cout << (char)('A' + c) << " ";
    cout << string(6, ' ');
    for (int c = 0; c < size; ++c) cout << (char)('A' + c) << " ";
    cout << "\n";
    cout << string(2, ' ') << string(size * 2, '-') << string(6, ' ') << string(size * 2, '-') << "\n";
    
    
    for (int r = 0; r < size; ++r) {

        // Left Side: Player Board (Shows ships + incoming shots)
        cout << setw(2) << r << "|"; 
        for (int c = 0; c < size; ++c) {
            
            // Check if we have been shot here first!
            char shot = incomingShots(r, c);
            if (shot != 0) {
                cout << shot << " "; 
            } else {
                int id = myBoard(r, c);
                char sym = '.';
                if (id > 0) {
                    Ship &s = *fleet[id - 1];
                    sym = s.getSymbol(); 
                }
                cout << sym << " ";
            }
        }
        
        cout << "   "; // Spacer

        // Right Side: Enemy Board (Shows my shots)
        cout << setw(2) << r << "|"; 
        for (int c = 0; c < size; ++c) {
            char mark = enemyBoard(r, c);
            if (mark == 0) mark = '.';
            cout << mark << " ";
        }

        cout << "\n";
    }

}

/**
 * @brief Helper to draw the placement interface with "ghost" ship.
 */
void HumanPlayer::drawPlacementView(Point cursor, bool vertical, Ship* s) const {

    // Clear screen
    cout << string(50, '\n');
    
    cout << "Place: " << s->getName() << " (Size " << s->getLength() << ", " << (vertical ? "Vertical" : "Horizontal") << ")\n";
    cout << "Controls: W/A/S/D move | C rotate | P place | Q quit\n";

    int size = getBoardSize(); 

    // Header
    cout << string(3, ' ');
    for (int c = 0; c < size; ++c) cout << (char)('A' + c) << " ";
    cout << "\n" << string(2, ' ') << string(size * 2, '-') << "\n";

    for (int r = 0; r < size; ++r) {
        cout << setw(2) << r << "|"; 
        
        for (int c = 0; c < size; ++c) {
            bool isGhost = false;
            
            // Render Ghost Ship at cursor
            for (int k = 0; k < s->getLength(); ++k) {
                int ghostR = cursor.row + (vertical ? k : 0);
                int ghostC = cursor.col + (vertical ? 0 : k);
                
                if (r == ghostR && c == ghostC) {
                    isGhost = true;
                    break;
                }
            }

            char sym = '.';
            int shipId = myBoard(r, c);
            
            if (isGhost) {
                sym = 'X'; 
            } else if (shipId > 0) {
                sym = fleet[shipId-1]->getSymbol(); 
            }
            
            cout << sym << " ";
        }
        cout << "\n";
    }
}

/**
 * @brief Interactive loop for user to place ships.
 * @return true if successful, false if user quits.
 */
bool HumanPlayer::placeShips() {
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
                case 'C': vertical = !vertical; break;
                case 'Q': 
                    return false;
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

    return true;
}

/**
 * @brief Prompts user for a target.
 * @param enemyShips Count of enemy ships for display.
 * @return Target point or Quit signal.
 */
Point HumanPlayer::makeMove(int enemyShips) {
    string input;
    int r, c, rowNum;
    char colChar;
    
    
    while (true) {
        cout << "Admiral, " << enemyShips << " ships are left. Choose your target (e.g. B3) or Q to quit: ";
        cin >> input;

        if (toupper(input[0]) == 'Q') {
            return Point::Quit();
        }
        
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
                        continue;
                    }
                }
            }
        }
        cout << "Invalid coordinate. Try again.\n";
    }
}

/**
 * @brief Constructor. Starts in Hunt mode.
 */
ComputerPlayer::ComputerPlayer() : Player("Computer") {
    huntMode = true;
}

/**
 * @brief Places ships randomly.
 * @return Always true.
 */
bool ComputerPlayer::placeShips() {
    placeShipsRandomly();
    return true;
}

/**
 * @brief Adds adjacent cells to the target stack after a hit.
 */
void ComputerPlayer::addAdjacentTargets(Point p) {
    potentialTargets.push_back(Point(p.row - 1, p.col));
    potentialTargets.push_back(Point(p.row + 1, p.col));
    potentialTargets.push_back(Point(p.row, p.col - 1));
    potentialTargets.push_back(Point(p.row, p.col + 1));
}

/**
 * @brief AI Logic: Switches between random Hunting and smart Targeting.
 */
Point ComputerPlayer::makeMove(int enemyShips) {
    Point target;
    bool valid = false;
    int size = getBoardSize();

    while (!valid) {
        if (potentialTargets.empty()) huntMode = true;

        if (huntMode) {
            // Fire randomly at the board
            target.row = rand() % size;
            target.col = rand() % size;
        } else {
            // Fire at adjacent spots found
            target = potentialTargets.back();
            potentialTargets.pop_back();
        }

        // Validate target
        if (target.row >= 0 && target.row < size && target.col >= 0 && target.col < size) {
            if (enemyBoard(target.row, target.col) == 0) valid = true;
        }
    }
    return target;
}