/* 
 * File: Player.h
 * Author: John Huynh
 * Purpose: Abstract base class for the Battleship player
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Grid.h" 
#include "Ships.h"
#include "Point.h"

#include <vector>
#include <string>

class Player {
    protected:

        std::string name;           // Player name
        Grid<int> myBoard;          // 0 = Empty, 1-5 = Ship IDs
        Grid<char> enemyBoard;      // X = Hit, O = Miss
        std::vector<Ship*> fleet;   // Dynamic list of ships
        int shipsRemaining;         // Number of ships remaining
        
        // Mutators
        void applyShipToBoard(Point p, bool vertical, int length, int shipId); // placeShip() function

        // Accessors
        bool canPlace(Point p, bool vertical, int length) const; // canPlace() function

    public:
        Player(std::string n);                                  // Sets name

        virtual ~Player();                                      // Destructor
        virtual void placeShips() = 0;                          // Player is manual, computer is random
        virtual Point makeMove() = 0;                           // Player is manual, computer is random, then targeted

        // Mutators
        void initFleet(int mode);
        void placeShipsRandomly();                              // Computer random fleet placement
        bool receiveShot(Point p, bool &wasHit, bool &sunk);    // Process shot

        // Getters
        std::string getName() const { return name; }
        int getBoardSize() const { return myBoard.getSize(); }  // Get board size
        bool hasLost() const;                                   // Check for winner
        
        // Helpers
        void printBoards() const;                               // Print board

};

#endif 