/* 
 * File:   main.cpp
 * Author: John Huynh
 * Created on October 18, 2025
 * Purpose: Division Sales Data using Structures
 */

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Division {
    string name;
    float qrt1, qrt2, qrt3, qrt4, total, average;
};

void getSales(Division &div, bool isLast);

int main() {
    Division north = {"North"};
    Division west  = {"West"};
    Division east  = {"East"};
    Division south = {"South"};
    
    getSales(north, false);
    getSales(west, false);
    getSales(east, false);
    getSales(south, true);
    
    return 0;
}

void getSales(Division &div, bool isLast) {
    cout << div.name << endl;
    cout << "Enter first-quarter sales:" << endl;
    cin >> div.qrt1;
    cout << "Enter second-quarter sales:" << endl;
    cin >> div.qrt2;
    cout << "Enter third-quarter sales:" << endl;
    cin >> div.qrt3;
    cout << "Enter fourth-quarter sales:" << endl;
    cin >> div.qrt4;
    
    div.total = div.qrt1 + div.qrt2 + div.qrt3 + div.qrt4;
    div.average = div.total / 4.0;
    
    cout << fixed << setprecision(2);
    cout << "Total Annual sales:$" << div.total << endl;
    cout << "Average Quarterly Sales:$" << div.average;
    
    if (!isLast) cout << endl;
}
