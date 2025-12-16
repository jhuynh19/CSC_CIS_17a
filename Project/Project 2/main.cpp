/* 
 * File: main.cpp
 * Author: John Huynh
 * Purpose: Setup and Run Battleship
 */

#include "Game.h"
#include <iostream>

using namespace std;

/**
 * @brief Main execution function.
 * Initializes the Game controller and starts the main loop.
 * @return 0 on successful execution.
 */
int main() {
    // Create the game controller instance
    Game battleship;

    // Start the game application loop
    battleship.run();

    return 0;
}