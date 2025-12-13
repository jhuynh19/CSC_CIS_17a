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

        std::string name;           
        Grid<int> myBoard;          
        Grid<char> enemyBoard;      
        std::vector<Ship*> fleet;   
        int shipsRemaining;         
        
        // Mutators
        void applyShipToBoard(Point p, bool vertical, int length, int shipId); 

        // Getters
        bool canPlace(Point p, bool vertical, int length) const; 

    private:
    // None needed

    public:
        Player(std::string n);                                  

        virtual ~Player();                                      
        virtual void placeShips() = 0;                         
        virtual Point makeMove() = 0;                          

        // Mutators
        void initFleet(int mode);
        void placeShipsRandomly();                              
        bool receiveShot(Point p, bool &wasHit, bool &sunk);    

        // Getters
        std::string getName() const { return name; }
        int getBoardSize() const { return myBoard.getSize(); }  
        bool hasLost() const;                                   
        
        // Helpers
        void printBoards() const;                              

        void setBoardSize(int s) {
            myBoard.resize(s);
            enemyBoard.resize(s);
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

        void placeShips() override;   
        Point makeMove() override;    
};

class ComputerPlayer : public Player {
    private:
        std::vector<Point> potentialTargets; 
        bool huntMode;
        Point lastHit;

    public:
        ComputerPlayer();
        virtual ~ComputerPlayer() {}

        void placeShips() override;
        Point makeMove() override;
        
        void addAdjacentTargets(Point p);
};

#endif 