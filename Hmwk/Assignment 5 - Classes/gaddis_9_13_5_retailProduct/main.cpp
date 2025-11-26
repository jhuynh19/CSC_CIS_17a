/*
 * File: main.cpp
 * Author: John Huynh
 * Date: November 24, 202
 * Purpose: Retail Item Class
*/

// Libraries
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Product {

    private:
        string description;  
        int stock;    
        float price;       

    public:

        Product(string desc, int stk, float p) {
            description = desc;
            stock = stk;
            price = p;
        }

        // Default Item
        Product() {
            description = "";
            stock = 0;
            price = 0.0;
        }

        // Mutators
        void setDescription(string desc) {
            description = desc;
        }
        void setUnitsOnHand(int stk) {
            stock = stk;
        }
        void setPrice(float p) {
            price = p;
        }

        string getDescription() const {
            return description;
        }
        int getUnitsOnHand() const {
            return stock;
        }
        float getPrice() const {
            return price;
        }

        // Display Item
        void display() const {
            cout << left << setw(20) << description << setw(15) << stock << fixed << setprecision(2) << "$" << price << endl;
        }

};

int main() {

    Product jacket("Jacket", 12, 59.95);
    Product jeans("Designer Jeans", 40, 34.95);
    Product shirt("Shirt", 20, 24.95);

    cout << left << setw(10) << " " << setw(20) << "Description" << setw(15) << "Units On Hand" << setw(5) << "Price" << endl;
    cout << string(54, '-') << "\n";

    cout << left << setw(10) << "Item #1";
    jacket.display();

    cout << left << setw(10) << "Item #2";
    jeans.display();

    cout << left << setw(10) << "Item #3";
    shirt.display();

    // Exit Stage Right
    cin.get();
    return 0;

}