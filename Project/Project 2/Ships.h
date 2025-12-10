/* 
 * File: Ships.h
 * Author: John Huynh
 * Purpose: Ship class and ship types
 */

#ifndef SHIPS_H
#define SHIPS_H

#include <string>
#include <iostream>

class Ship {
    protected:
        std::string name;
        int length;
        int damage;

    private:
    // None needed

    public:
    
        // Constructor
        Ship(std::string n, int l) : name(n), length(l), damage(0) {};

        // Destructor
        virtual ~Ship() {}

        // Getters
        std::string getName() const { return name; }
        int getLength() const { return length; }
        int getDamage() const { return damage; }
        bool isSunk() const { return damage >= length; }

        // Accessor
        virtual char getSymbol() const = 0;

        // Mutators
        virtual void takeHit() {
            damage++;
        }
        
};

class Carrier : public Ship {
    public:
        Carrier() : Ship("Aircraft Carrier", 5) {}
        char getSymbol() const override { return 'A'; }
};

class Battleship : public Ship {
    public:
        Battleship() : Ship("Battleship", 4) {}
        char getSymbol() const override { return 'B'; }
};

class Cruiser : public Ship {
    public:
        Cruiser() : Ship("Cruiser", 3) {}
        char getSymbol() const override { return 'R'; }
};

class Submarine : public Ship {
    public:
        Submarine() : Ship("Submarine", 3) {}
        char getSymbol() const override { return 'S'; }
};

class Destroyer : public Ship {
    public:
        Destroyer() : Ship("Destroyer", 2) {}
        char getSymbol() const override { return 'D'; }
};

#endif