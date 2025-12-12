/* 
 * File: Game.h
 * Author: John Huynh
 * Purpose: Game Management
 */

#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include <fstream>

class Game {
    protected:
    // None needed
    
    private:
        Player* player;     
        Player* computer;     

        static int gamesPlayed;

        struct Stats {
            unsigned int totalGames;
            unsigned int userWins;
        };

        Stats currentStats;

        void loadStats();
        void saveStats();

    public:
        Game();
        ~Game();

        void setup();

        void play();

        void displayStats() const;
        
        static int getGamesPlayed() { return gamesPlayed; }
};

#endif
