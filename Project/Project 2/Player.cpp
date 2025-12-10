/* 
 * File:   Player.cpp
 * Author: John Huynh
 * Purpose: Player logic
 */

// Libraries
#include "Player.h"
#include <iostream>
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