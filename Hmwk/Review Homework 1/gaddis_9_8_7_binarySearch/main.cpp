/* 
 * File: main.cpp
 * Author: John Huynh
 * Created on September 9th, 2025, 10:00 PM
 * Purpose: Modify the binarySearch function presented in this chapter so it searches an array of strings instead of an array of ints. Test the function with a driver program. Use Programming Challenges 533 Program 8-8 as a skeleton to complete. (The array must be sorted before the binary search will work.)
 */

//System Libraries
#include <iostream>
#include <iomanip>

using namespace std;

// Prototypes
int binarySearch(const string[], int, string);
const int SIZE = 20; 

// Main Function
int main()
{
    // Array with employee IDs sorted in ascending order.
    string ids[SIZE] = {"101", "142", "147", "189", "199", "207", "222",
                        "234", "289", "296", "310", "319", "388", "394",
                        "417", "429", "447", "521", "536", "600"};

    int results;   // To hold the search results
    string id;     // Holder for employee name

    // Get an employee id to search for.
    cout << "Enter the employee ID you wish to search for: ";
    cin >> id;

    // Search for them by name.
    results = binarySearch(ids, SIZE, id);

    // If results contains -1 the ID was not found.
    if (results == -1)
        cout << id << "That number does not exist in the array. \n";
    else
    {
        cout << id << " is found at element " << results;
        cout << " in the array.\n";
    }
    return 0;
}


int binarySearch(const string array[], int numElems, string value)
{
    int first = 0,                 // First array element
        last = numElems - 1,       // Last array element
        middle,                    // Midpoint of search
        position = -1;             // Position of search value
    bool found = false;            // Flag

    while (!found && first <= last)
    {
        middle = (first + last) / 2;           // Calculate midpoint
        if (array[middle] == value)            // If value is found at mid
        {
            found = true;
            position = middle;
        }
        else if (array[middle] > value)        // If value is in lower half
            last = middle - 1;
        else
            first = middle + 1;                // If value is in upper half
    }
    return position;
}
