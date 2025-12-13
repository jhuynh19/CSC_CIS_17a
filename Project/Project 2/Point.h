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

        // Helpers
        static Point Quit() { return Point(-1, -1); }
        bool isQuit() const { return row == -1 && col == -1; }

        // Parameterized Constructor
        Point(int r = 0, int c = 0) : row(r), col(c) {}
    
        // Operators
        Point operator+(const Point& right) const {                            
            return Point(row + right.row, col + right.col);
        }

        bool operator==(const Point& right) const {
            return (row == right.row && col == right.col);                      
        }

        bool operator!=(const Point& right) const {                                         
            return !(*this == right);
        }

        friend std::ostream& operator<<(std::ostream& out, const Point& p) {    
            out << (char)('A' + p.col) << p.row;
            return out;
        }

};

#endif