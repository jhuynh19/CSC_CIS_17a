/* 
 * File:   main.cpp
 * Author: John Huynh
 * Created on: September 17, 2025
 * Purpose:  To tell the Truth
 */

//System Libraries Here
#include <iostream>
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here
void cmpTable(bool x, bool y);

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    int xVals[5];
    int yVals[5];
    int n = 0;
    
    //Display the Heading
    cout << "X Y !X !Y X&&Y X||Y X^Y X^Y^X X^Y^Y !(X&&Y) !X||!Y " << " !(X||Y) !X&&!Y" << endl;
    
    while (cin >> xVals[n] >> yVals[n]) {
        n++;
    }
    
    for (int i = 0; i < n; i++) {
        bool x = (xVals[i]);
        bool y = (yVals[i]);
        cmpTable(x, y);
    }
    
    cout << endl;
    
    //Exit
    return 0;
}

void cmpTable(bool x, bool y) {
    cout << ((x)?'T':'F') << " "
         << ((y)?'T':'F') << "  "
         << ((!x)?'T':'F') << "  "
         << ((!y)?'T':'F') << "   "
         << ((x && y)?'T':'F') << "    "
         << ((x || y)?'T':'F') << "   "
         << ((x ^ y)?'T':'F') << "    "
         << ((x ^ y ^ x)?'T':'F') << "     "
         << ((x ^ y ^ y)?'T':'F') << "       "
         << (!(x && y)?'T':'F') << "      "
         << ((!x || !y)?'T':'F') << "        "
         << (!(x || y)?'T':'F') << "      "
         << ((!x && !y)?'T':'F')
         << endl;
}