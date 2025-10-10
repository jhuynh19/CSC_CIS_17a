/* 
 * File:  main.cpp
 * Author: John Huynh
 * Created on September 28, 2025
 */

#include <iostream>
using namespace std;


int **getData (int &rows, int &cols); //Get the Matrix Data
void prntDat (const int * const *array2D, int rows, int cols); //Print the Matrix
int **augment (const int *const *array2D, int rows, int cols); //Augment the original array
void destroy (int **array2D, int rows); //Destroy the Matrix, i.e., reallocate memory

// Main
int main () {
    
    int rows, cols;
    int **array2D = getData(rows, cols);
    int **augMatrix = augment(array2D, rows, cols);

    prntDat(array2D, rows, cols);
    
    cout << "\n";
    
    prntDat(augMatrix, rows + 1, cols + 1);

    destroy(array2D, rows);
    destroy(augMatrix, rows + 1);

    return 0;
}

//Get the Matrix Data
int **getData (int &rows, int &cols) {
    cin >> rows >> cols;
    int **array2D = new int *[rows];
    for (int i = 0; i < rows; ++i) {
        
        array2D[i] = new int[cols];
        
        for (int j = 0; j < cols; ++j) {
            
            cin >> array2D[i][j];
            
        }
        
    }
    
    return array2D;
}

//Print the Matrix
void prntDat (const int *const *array2D, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << array2D[i][j];
            if (j < cols - 1) cout << " ";
        }
        if (i < rows - 1) cout << "\n";
    }
}

//Augment the original array
int **augment (const int *const *array2D, int rows, int cols) {
    
    int newRows = rows + 1;
    int newCols = cols + 1;
    int * * aug = new int * [newRows];

    for (int i = 0; i < newRows; ++i) aug[i] = new int[newCols];
    for (int j = 0; j < newCols; ++j) aug[0][j] = 0;
    for (int i = 0; i < newRows; ++i) aug[i][0] = 0;

    for (int i = 0; i < rows; ++i) {
        
        for (int j = 0; j < cols; ++j) {
            
            aug[i + 1][j + 1] = array2D[i][j];
            
        }
        
    }

    return aug;
}

//Destroy the Matrix, i.e., reallocate memory
void destroy (int **array2D, int rows) {
    
    for (int i = 0; i < rows; ++i) {
        
        delete [] array2D[i];
        
    }
    
    delete [] array2D;
    
}
