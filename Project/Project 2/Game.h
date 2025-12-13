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

        struct GameRecord {
            unsigned int gameId;
            bool playerWon;

            char playerShots[10][10];
            char cpuShots[10][10];
        };

        void loadStats();
        void saveStats();
        void saveGameRecord(bool playerWon);

    public:
        Game();
        ~Game();

        void run();
        void setup();
        void play();
        void displayStats() const;
        void displayHistory() const;
        
        static int getGamesPlayed() { return gamesPlayed; }
};

#endif
