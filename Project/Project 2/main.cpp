/* 
 * File: main.cpp
 * Author: John Huynh
 * Purpose: Setup and Play Battleship
 */

#include "Game.h"
#include <iostream>

using namespace std;

int main() {
    Game battleship;

    battleship.setup();
    battleship.play();
    battleship.displayStats();

    return 0;
}