/* 
 * File:   main.cpp
 * Author: John Huynh
 * Created on October 18, 2025
 * Purpose: Monthly Budget Using Structures
 */

#include <iostream>
#include <iomanip>
using namespace std;

struct MonthlyBudget {
    float housing, utilities, householdExp, transportation, food, medical, insurance, entertainment, clothing, misc;
};

//Function Prototypes
void budgetCat(const char *label, float budget, float spent);

// Execution Begins Here
int main() {

    // Delcare Variable Data Types and Constants
    const MonthlyBudget B = {
        500.00,  // Housing
        150.00,  // Utilities
        65.00,   // Household Expenses
        50.00,   // Transportation
        250.00,  // Food
        30.00,   // Medical
        100.00,  // Insurance
        150.00,  // Entertainment
        75.00,   // Clothing
        50.00    // Miscellaneous
    };

    MonthlyBudget S{}; 

    // Initialize Variables
    cout << "Enter housing cost for the month:$" << endl;
    cin >> S.housing;

    cout << "Enter utilities cost for the month:$" << endl;
    cin >> S.utilities;

    cout << "Enter household expenses cost for the month:$" << endl;
    cin >> S.householdExp;
    
    cout << "Enter transportation cost for the month:$" << endl;
    cin >> S.transportation;

    cout << "Enter food cost for the month:$" << endl;
    cin >> S.food;

    cout << "Enter medical cost for the month:$" << endl;
    cin >> S.medical;

    cout << "Enter insurance cost for the month:$" << endl;
    cin >> S.insurance;

    cout << "Enter entertainment cost for the month:$" << endl;
    cin >> S.entertainment;

    cout << "Enter clothing cost for the month:$" << endl;
    cin >> S.clothing;

    cout << "Enter miscellaneous cost for the month:$" << endl;
    cin >> S.misc;

    // Process or map Inputs to Outputs
    budgetCat("Housing", B.housing, S.housing);
    budgetCat("Utilities", B.utilities, S.utilities);
    budgetCat("Household Expenses", B.householdExp, S.householdExp);
    budgetCat("Transportation", B.transportation, S.transportation);
    budgetCat("Food", B.food, S.food);
    budgetCat("Medical", B.medical, S.medical);
    budgetCat("Insurance", B.insurance, S.insurance);
    budgetCat("Entertainment", B.entertainment, S.entertainment);
    budgetCat("Clothing", B.clothing, S.clothing);
    budgetCat("Miscellaneous", B.misc, S.misc);

    float budgetTot = B.housing + B.utilities + B.householdExp + B.transportation + B.food + B.medical + B.insurance + B.entertainment + B.clothing + B.misc;

    float spendTot = S.housing + S.utilities + S.householdExp + S.transportation + S.food + S.medical + S.insurance + S.entertainment + S.clothing + S.misc;

    float diff = budgetTot - spendTot;   

    int sign = (diff > 0.0f) ? 1 : ((diff < 0.0f) ? -1 : 0);

    // Display Outputs
    cout << fixed << setprecision(2);

    switch (sign) {

        case 1:
            cout << "You were $" << diff << " under budget";
            break;

        case -1:
            cout << "You were $" << (diff * -1) << " over budget";
            break;

        default:
            cout << "Your spending matched your budget";
            break;

    }

    // Exit stage right!
    return 0;
}

void budgetCat(const char *label, float budget, float spending) {

    if (spending < budget) 
        cout << label << " Under" << endl;
    else if (spending > budget) 
        cout << label << " Over" << endl;
    else                    
        cout << label << " Even" << endl;

}