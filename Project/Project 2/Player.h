/* 
 * File: Player.h
 * Author: John Huynh
 * Purpose: Player class and derived types (Human/Computer)
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Grid.h" 
#include "Ships.h"
#include "Point.h"
#include <vector>
#include <string>

/**
 * @class Player
 * @brief Base class for all players.
 * Handles the game boards, fleet management, and shot logic.
 */
class Player {

    // Allows the Game class to access protected members like the boards
    friend class Game;

    protected:
        std::string name;           ///< Player's name
        Grid<int> myBoard;          ///< Where player's ships are (0=empty, ID=ship)
        Grid<char> enemyBoard;      ///< Where player has shot ('X'=hit, 'O'=miss)
        Grid<char> incomingShots;   ///< Where player has been shot
        std::vector<Ship*> fleet;   ///< List of player ships
        int shipsRemaining;         ///< How many ships are still alive
        
        /**
         * @brief Writes ship ID numbers onto the board grid.
         */
        void applyShipToBoard(Point p, bool vertical, int length, int shipId); 

        /**
         * @brief Checks if a ship fits on the board without overlapping.
         */
        bool canPlace(Point p, bool vertical, int length) const; 

    public:
 
        Player(std::string n);                                  
        virtual ~Player();                          
        
        /**
         * @brief Handles ship setup. Returns false if user quits.
         */
        virtual bool placeShips() = 0;       
        
        /**
         * @brief Determines the next shot target.
         * @param enemyShips Used for the prompt text.
         */
        virtual Point makeMove(int enemyShips) = 0;

        /**
         * @brief Creates the fleet based on game mode (Standard vs Rapid).
         */
        void initFleet(int mode);

        /**
         * @brief Randomly places all ships (used by Computer).
         */
        void placeShipsRandomly();                              
        
        /**
         * @brief Processes a shot fired at this player.
         * @param sunkName If a ship sinks, this string gets updated with its name.
         * @return true if valid shot, false if out of bounds.
         */
        bool receiveShot(Point p, bool &wasHit, bool &sunk, std::string &sunkName); 

        // Getters
        std::string getName() const { return name; }
        int getBoardSize() const { return myBoard.getSize(); }  
        int getShipsRemaining() const { return shipsRemaining; }
        bool hasLost() const;                                     
        
        /**
         * @brief displays both boards (My Board vs Enemy Board) side-by-side.
         */
        void printBoards() const;                              

        void setBoardSize(int s) {
            myBoard.resize(s);
            enemyBoard.resize(s);
            incomingShots.resize(s);
        }

        // Marks the result of player's shot on the tracking board
        void markShot(Point p, bool hit) {
            enemyBoard(p.row, p.col) = (hit ? 'X' : 'O');
        }
};

/**
 * @class HumanPlayer
 * @brief Handles user input for ship placement and targeting.
 */
class HumanPlayer : public Player {
    private:
        // Visual interface for the "WASD" placement mode
        void drawPlacementView(Point cursor, bool vertical, Ship* s) const;

    public:
        HumanPlayer(std::string n) : Player(n) {}
        virtual ~HumanPlayer() {}

        bool placeShips() override;
        Point makeMove(int enemyShips) override;    
};

/**
 * @class ComputerPlayer
 * @brief AI opponent with a simple Hunt/Target strategy.
 */
class ComputerPlayer : public Player {
    private:
        std::vector<Point> potentialTargets;    ///< Stack of adjacent cells to try after a hit
        bool huntMode;                          ///< True = Searching randomly, False = Targeting specific area
        Point lastHit;

    public:
        ComputerPlayer();
        virtual ~ComputerPlayer() {}

        bool placeShips() override;
        Point makeMove(int enemyShips) override;
        
        // Pushes Up/Down/Left/Right coordinates to the target stack
        void addAdjacentTargets(Point p);
};

#endif 