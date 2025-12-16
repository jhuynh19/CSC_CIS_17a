/* 
 * File: Game.h
 * Author: John Huynh
 * Purpose: Game Management
 */

#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include <fstream>

/**
 * @class Game
 * @brief Main controller for the Battleship application.
 * Manages the game loop, player creation, statistics, and file I/O.
 */
class Game {
    private:
        Player* player;     ///< Pointer to the human player
        Player* computer;   ///< Pointer to the computer player

        static int gamesPlayed;

        /**
         * @struct Stats
         * @brief Structure for persistent player statistics.
         */
        struct Stats {
            unsigned int totalGames;
            unsigned int userWins;
            unsigned int shotsHit;
            unsigned int shotsMissed;
        };

        Stats currentStats; ///< Holds currently loaded statistics

        /**
         * @struct GameRecord
         * @brief Structure for saving game history snapshots.
         */
        struct GameRecord {
            unsigned int gameId;
            bool playerWon;
            int boardSize;
            char playerShots[10][10];
            char cpuShots[10][10];
        };

        /**
         * @brief Loads statistics from the binary file.
         */
        void loadStats();

        /**
         * @brief Saves current statistics to the binary file.
         */
        void saveStats();

        /**
         * @brief Appends the result of the last game to the history file.
         * @param playerWon True if the human won.
         */
        void saveGameRecord(bool playerWon);

    public:
        /**
         * @brief Constructor. Initializes pointers and loads stats.
         */
        Game();

        /**
         * @brief Destructor. Cleans up player memory.
         */
        ~Game();

        /**
         * @brief Runs the main application menu loop.
         * Handles options for Play, Stats, History, and Quit.
         */
        void run();

        /**
         * @brief Handles game configuration (Mode selection, Fleet init).
         */
        void setup();

        /**
         * @brief Executes the actual gameplay loop (Turns, Shots, Win Check).
         */
        void play();

        /**
         * @brief Displays persistent statistics to the console.
         */
        void displayStats() const;

        /**
         * @brief Reads and displays past game history from the binary file.
         */
        void displayHistory() const;
        
        /**
         * @brief Static getter for session game count.
         */
        static int getGamesPlayed() { return gamesPlayed; }
};

#endif
