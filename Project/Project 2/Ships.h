/* 
 * File: Ships.h
 * Author: John Huynh
 * Purpose: Defines the Ship base class and specific ship types.
 */

#ifndef SHIPS_H
#define SHIPS_H

#include <string>
#include <iostream>

/**
 * @class Ship
 * @brief Abstract base class for all ship types.
 * Tracks name, length, and damage.
 */
class Ship {
    protected:
        std::string name;
        int length;
        int damage;

    public:
    
        /**
         * @brief Constructor.
         * @param n Name of ship.
         * @param l Length of ship.
         */
        Ship(std::string n, int l) : name(n), length(l), damage(0) {};

        // Destructor
        virtual ~Ship() {}

        // Getters
        std::string getName() const { return name; }
        int getLength() const { return length; }
        int getDamage() const { return damage; }

        /**
         * @brief Returns true if damage equals length.
         */
        bool isSunk() const { return damage >= length; }

        /**
         * @brief Returns the char symbol for the board.
         */
        virtual char getSymbol() const = 0;

        /**
         * @brief Increments damage when hit.
         */
        virtual void takeHit() {
            damage++;
        }
        
};

/**
 * @class Carrier
 * @brief Size 5 Ship. Symbol: 'A'
 */
class Carrier : public Ship {
    public:
        Carrier() : Ship("Aircraft Carrier", 5) {}
        char getSymbol() const override { return 'A'; }
};

/**
 * @class Battleship
 * @brief Size 4 Ship. Symbol: 'B'
 */
class Battleship : public Ship {
    public:
        Battleship() : Ship("Battleship", 4) {}
        char getSymbol() const override { return 'B'; }
};

/**
 * @class Cruiser
 * @brief Size 3 Ship. Symbol: 'R'
 */
class Cruiser : public Ship {
    public:
        Cruiser() : Ship("Cruiser", 3) {}
        char getSymbol() const override { return 'R'; }
};

/**
 * @class Submarine
 * @brief Size 3 Ship. Symbol: 'S'
 */
class Submarine : public Ship {
    public:
        Submarine() : Ship("Submarine", 3) {}
        char getSymbol() const override { return 'S'; }
};

/**
 * @class Destroyer
 * @brief Size 2 Ship. Symbol: 'D'
 */
class Destroyer : public Ship {
    public:
        Destroyer() : Ship("Destroyer", 2) {}
        char getSymbol() const override { return 'D'; }
};

#endif