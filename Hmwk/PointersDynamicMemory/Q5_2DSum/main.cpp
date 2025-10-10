/* 
 * File:  main.cpp
 * Author: John Huynh
 * Created on September 27, 2025
 */

#include <iostream>
using namespace std;


int **getData (int &rows, int &cols); //Return the 2-D array and its size
void prntDat (const int *const *array2D, int rows, int cols); //Print the 2-D Array
void destroy (int **array2D, int rows, int cols); //Deallocate memory
int sum (const int *const *array2D, int rows, int cols); //Return the Sum

// Main
int main () {
    int rows, cols;
    int **array2D = getData(rows, cols);

    prntDat(array2D, rows, cols);
    cout << sum(array2D, rows, cols);

    destroy(array2D, rows, cols);

    return 0;
}

//Return the 2-D array and its size.
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

void prntDat (const int *const *array2D, int rows, int cols) {
    
    for (int i = 0; i < rows; ++i) {
        
        for (int j = 0; j < cols; ++j) {
            
            cout << array2D[i][j];
            
            if (j < cols - 1) cout << " ";
            
        }
        
        cout << "\n";
        
    }
    
}

void destroy (int **array2D, int rows, int cols) {
    
    for (int i = 0; i < rows; ++i) {
        
        delete [] array2D[i];
        
    }
    
    delete [] array2D;
    
}

int sum (const int *const *array2D, int rows, int cols) {
    
    int total = 0;
    
    for (int i = 0; i < rows; ++i) {
        
        for (int j = 0; j < cols; ++j) {
            
            total += array2D[i][j];
            
        }
        
    }
    
    return total;
    
}
