/* 
 * File: Point.h
 * Author: John Huynh
 * Purpose: Coords system for the Battleship board
 */

#ifndef POINT_H
#define POINT_H

#include <iostream>  

class Point {
    protected:
    // None needed
    
    private:
    // None needed

    public:
        int row;
        int col;

        // Parameterized Constructor
        Point(int r = 0, int c = 0) : row(r), col(c) {}
    
        // Operators
        Point operator+(const Point& right) const {                             // Adds two points together
            return Point(row + right.row, col + right.col);
        }

        bool operator==(const Point& right) const {
            return (row == right.row && col == right.col);                      // Checks if two points share the exact same coordinates
        }

        bool operator!=(const Point& right) const {                             // Returns true if the points are different            return !(*this == right);
        }

        friend std::ostream& operator<<(std::ostream& out, const Point& p) {    // Print Point object
            out << (char)('A' + p.col) << p.row;
            return out;
        }

};

#endif