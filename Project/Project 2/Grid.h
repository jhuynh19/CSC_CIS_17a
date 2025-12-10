/* 
 * File:   Grid.h
 * Author: John Huynh
 * Purpose: Class for game boards
 */

#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <vector>
#include <stdexcept>

template <class T>
class Grid {
protected:
    int size;
    T** data;
    
private:
    // None needed

public:

    // Constructor (Allocated Memory for Array)
    Grid(int s = 10) : size(s) {
        data = new T*[size];

        for (int i = 0; i < size; i++) {
            data[i] = new T[size]{};
        }
    }

    // Destructor
    ~Grid() {
        if (data) {
            for (int i = 0; i < size; i++) {
                delete[] data[i];
            }
            delete[] data;
        }
    }

    Grid(const Grid &obj) {
        size = obj.size;
        data = new T*[size];

        for (int i = 0; i < size; i++) {

            data[i] = new T[size];

            for (int j = 0; j < size; j++) {
                data[i][j] = obj.data[i][j]; 
            }
        }
    }

    // Operator Overloading
    T& operator()(int r, int c) {
        if (r < 0 || r >= size || c < 0 || c >= size) {
            throw std::out_of_range("Grid index out of bounds");
        }
        return data[r][c];
    }
    
    // Read Coords
    const T& operator()(int r, int c) const {
        if (r < 0 || r >= size || c < 0 || c >= size) {
            throw std::out_of_range("Grid index out of bounds");
        }
        return data[r][c];
    }

    // Getter
    int getSize() const { return size; }

};

#endif