/* 
 * File: Point.h
 * Author: John Huynh
 * Purpose: Coords system for the Battleship board
 */

#ifndef POINT_H
#define POINT_H

#include <iostream>  

/**
 * @class Point
 * @brief Represents a (row, column) coordinate on the game board.
 */
class Point {
    public:
        int row; ///< Row index (0-9)
        int col; ///< Column index (0-9)

        /**
         * @brief Constructor. Defaults to (0,0).
         */
        Point(int r = 0, int c = 0) : row(r), col(c) {}

        /**
         * @brief Returns a special coordinate (-1, -1) signaling a Quit action.
         */
        static Point Quit() { return Point(-1, -1); }

        /**
         * @brief Checks if this point represents a Quit signal.
         */
        bool isQuit() const { return row == -1 && col == -1; }
    
        /**
         * @brief Adds two points together (used for relative movement).
         */
        Point operator+(const Point& right) const {                            
            return Point(row + right.row, col + right.col);
        }

        /**
         * @brief Equality check.
         */
        bool operator==(const Point& right) const {
            return (row == right.row && col == right.col);                      
        }

        /**
         * @brief Inequality check.
         */
        bool operator!=(const Point& right) const {                                         
            return !(*this == right);
        }

        /**
         * @brief Stream insertion operator.
         * Prints coordinate in "A1" format (Column Letter + Row Number).
         */
        friend std::ostream& operator<<(std::ostream& out, const Point& p) {    
            out << (char)('A' + p.col) << p.row;
            return out;
        }

};

#endif