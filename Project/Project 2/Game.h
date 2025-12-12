/* 
 * File: Game.h
 * Author: John Huynh
 * Purpose: Game Management
 */

#ifndef GAME_H
#define GAME_H

#include "Player.h"

class Game {
    protected:
    // None needed
    
    private:
        Player* player;     
        Player* computer;     

        static int gamesPlayed;

    public:
        Game();
        ~Game();

        void setup();

        void play();
        
        static int getGamesPlayed() { return gamesPlayed; }
};

#endif
