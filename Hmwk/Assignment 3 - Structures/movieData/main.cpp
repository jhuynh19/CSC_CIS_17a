/* 
 * File:   main.cpp
 * Author: John Huynh
 * Created on October 21, 2025
 * Purpose: Movie Database
 */

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct MovieData {
    string title, director;
    int relYear, runTime; 
};

// Function Prototypes
void displayMovieInfo(const MovieData &movie);

// Main
int main() {
    int numMovies;

    cout << "This program reviews structures" << endl;
    cout << "Input how many movies, the Title of the Movie, Director, Year Released, and the Running Time in (minutes)." << endl;
    cout << endl;
    cin >> numMovies;
    cin.ignore();

    // Create movie list
    MovieData *movies = new MovieData[numMovies];

    // Input data for each movie
    for (int i = 0; i < numMovies; i++) {
        getline(cin, movies[i].title);
        getline(cin, movies[i].director);
        cin >> movies[i].relYear;
        cin >> movies[i].runTime;
        cin.ignore();
    }

    // Display all movies
    for (int i = 0; i < numMovies; i++) {
        displayMovieInfo(movies[i]);

        if (i != numMovies - 1) cout << endl;

    }

    // Exit stage right
    delete[] movies;
    return 0;
}

// Display info for each movie
void displayMovieInfo(const MovieData &movie) {
    cout << setw(11) << left << "Title: " << movie.title << endl;
    cout << setw(11) << left << "Director: " << movie.director << endl;
    cout << setw(11) << left << "Year: " << movie.relYear << endl;
    cout << setw(11) << left << "Length: " << movie.runTime << endl;
}
