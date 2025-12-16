/* 
 * File: Grid.h
 * Author: John Huynh
 * Purpose: Class for game boards
 */

#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <vector>
#include <stdexcept>

/**
 * @class Grid
 * @brief A 2D array wrapper that manages memory safely.
 * Uses templates to store any data type (int for IDs, char for markers).
 */
template <class T>

class Grid {
    protected:
        int size; ///< Width/Height of the square grid
        T** data; ///< Pointer to the dynamic 2D array
        
    public:

        /**
         * @brief Constructor. Allocates memory and initializes to zero/null.
         * @param s Size of the grid (default 10).
         */
        Grid(int s = 10) : size(s) {
            data = new T*[size];

            for (int i = 0; i < size; i++) {
                data[i] = new T[size]{};
            }
        }

        /**
         * @brief Destructor. Frees dynamically allocated memory.
         */
        ~Grid() {
            if (data) {
                for (int i = 0; i < size; i++) {
                    delete[] data[i];
                }
                delete[] data;
            }
        }
        
        /**
         * @brief Copy Constructor. Performs a deep copy of the grid.
         */
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

        /**
         * @brief Access operator for modifying data.
         * @param r Row index.
         * @param c Column index.
         * @return Reference to the element.
         * @throws std::out_of_range if index is invalid.
         */
        T& operator()(int r, int c) {
            if (r < 0 || r >= size || c < 0 || c >= size) {
                throw std::out_of_range("Grid index out of bounds");
            }
            return data[r][c];
        }
        
        /**
         * @brief Access operator for reading data (const).
         */
        const T& operator()(int r, int c) const {
            if (r < 0 || r >= size || c < 0 || c >= size) {
                throw std::out_of_range("Grid index out of bounds");
            }
            return data[r][c];
        }

        int getSize() const { return size; }

        /**
         * @brief Resizes the grid. WARNING: Clears all existing data.
         * @param newSize The new dimension for the square grid.
         */
        void resize(int newSize) {
            if (size == newSize) return; 

            // Delete old memory
            if (data) {
                for (int i = 0; i < size; i++) {
                    delete[] data[i];
                }
                delete[] data;
            }

            // Allocate new memory
            size = newSize;
            data = new T*[size];
            for (int i = 0; i < size; i++) {
                data[i] = new T[size]{}; 
            }
        }

};

#endif