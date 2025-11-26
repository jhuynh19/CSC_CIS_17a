/*
 * File: main.cpp
 * Author: John Huynh
 * Date: November 24, 2025
 * Purpose: Retail Item Class w/ Pricing
*/

// Libraries
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Inventory {

    private:
        int itemNumber;
        int quantity;
        double cost;
        double totalCost; 

    public:
        Inventory(int sku, int qty, double c) {
            setItemNumber(sku);
            setQuantity(qty);
            getCost(c);
            setTotalCost(); 
        }

        // Default Item Values
        Inventory() {
            itemNumber = 0;
            quantity = 0;
            cost = 0.0;
            totalCost = 0.0;
        }

        // Calculate Subtotal
        void setTotalCost() {
            totalCost = quantity * cost;
        }

        // Mutators
        void setItemNumber(int sku) {

            if (sku < 0) {
                cout << "Err: SKU cannot be negative. Setting to 0.\n";
                itemNumber = 0;
            } else {
                itemNumber = sku;
            }
            
        }
        void setQuantity(int qty) {

            if (qty < 0) {
                cout << "Err: Quantity cannot be negative. Setting to 0.\n";
                quantity = 0;
            } else {
                quantity = qty;
            }

            setTotalCost();
        }

        void getCost(double c) {

            if (c < 0) {
                cout << "Err: Cost cannot be negative. Setting to 0.0.\n";
                cost = 0.0;
            } else {
                cost = c;
            }

            setTotalCost();

        }

        int getItemNumber() const { 
            return itemNumber;
        }
        int getQuantity() const { 
            return quantity;
        }
        double getCost() const { 
            return cost;
        }
        double getTotalCost() const { 
            return totalCost;
        }

        // Display Item
        void display() const {
            cout << left << setw(10) << itemNumber << setw(10) << quantity << fixed << setprecision(2) << "$" << setw(14) << cost << "$" << totalCost << endl;
        }
};

int main() {

    // Tshirt
    Inventory tshirt(129204, 1, 9.99);

    // Keychain
    Inventory keychain;
    keychain.setItemNumber(120945);
    keychain.setQuantity(4);
    keychain.getCost(3.99);

    // Invalid Item
    Inventory negative(-5, -10, -25.00);

    // Display 
    cout << "\n" << left << setw(10) << "SKU" << setw(10) << "Quantity" << setw(15) << "Unit Price" << setw(12) << "Total Cost" << endl;
    cout << string(50, '-') << endl;

    // Display Items
    tshirt.display();
    keychain.display();
    negative.display();

    // Exit Stage Right
    cin.get();
    return 0;

}