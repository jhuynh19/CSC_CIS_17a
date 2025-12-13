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

    friend class Game;

    protected:

        std::string name;           
        Grid<int> myBoard;          
        Grid<char> enemyBoard;      
        Grid<char> incomingShots;
        std::vector<Ship*> fleet;   
        int shipsRemaining;         
        
        // Mutators
        void applyShipToBoard(Point p, bool vertical, int length, int shipId); 
        bool canPlace(Point p, bool vertical, int length) const; 

    private:
    // None needed

    public:
        Player(std::string n);                                  

        virtual ~Player();                                      
        virtual bool placeShips() = 0;                         
        virtual Point makeMove(int enemyShips) = 0;

        // Mutators
        void initFleet(int mode);
        void placeShipsRandomly();                              
        bool receiveShot(Point p, bool &wasHit, bool &sunk, std::string &sunkName); 

        // Getters
        std::string getName() const { return name; }
        int getBoardSize() const { return myBoard.getSize(); }  
        int getShipsRemaining() const { return shipsRemaining; }
        bool hasLost() const;                                   
        
        // Helpers
        void printBoards() const;                              

        void setBoardSize(int s) {
            myBoard.resize(s);
            enemyBoard.resize(s);
            incomingShots.resize(s);
        }

        void markShot(Point p, bool hit) {
            enemyBoard(p.row, p.col) = (hit ? 'X' : 'O');
        }
};

class HumanPlayer : public Player {
    private:
        void drawPlacementView(Point cursor, bool vertical, Ship* s) const;

    public:
        HumanPlayer(std::string n) : Player(n) {}
        virtual ~HumanPlayer() {}

        bool placeShips() override;
        Point makeMove(int enemyShips) override;    
};

class ComputerPlayer : public Player {
    private:
        std::vector<Point> potentialTargets; 
        bool huntMode;
        Point lastHit;

    public:
        ComputerPlayer();
        virtual ~ComputerPlayer() {}

        bool placeShips() override;
        Point makeMove(int enemyShips) override;
        
        void addAdjacentTargets(Point p);
};

#endif 