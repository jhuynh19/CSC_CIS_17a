/* 
 * File: main.cpp
 * Author: John Huynh
 * Created on 12/03/2025
 * Purpose: Create Essay Class derived from GradedActivity
 */

// Libraries
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class GradedActivity {
    private:
        float score;

    public:
        // Default Constructor
        GradedActivity() { score = 0.0; }

        // Constructor
        GradedActivity(float s) { score = s; }

        // Mutator function
        void setScore(float s) {
            score = s; 
        }

        // Getter function
        float getScore() const { 
            return score; 
        }

        // Assign Letter Grade
        char getLetterGrade() const {
            char letterGrade;
            int scoreRange = static_cast<int>(score) / 10;

            switch (scoreRange) {
                case 10:
                case 9:
                    letterGrade = 'A';
                    break;
                case 8:
                    letterGrade = 'B';
                    break;
                case 7:
                    letterGrade = 'C';
                    break;
                case 6:
                    letterGrade = 'D';
                    break;
                default: 
                    letterGrade = 'F';
            }
            
            return letterGrade;
        }
};

class Essay : public GradedActivity {
    private:
        string student;
        int grammar;    
        int spelling;   
        int length;     
        int content;    

        void calculateTotalScore() {
            float total = grammar + spelling + length + content;
            setScore(total); 
        }

    public:
        // Default
        Essay() : GradedActivity(), student(""), grammar(0), spelling(0), length(0), content(0) {}

        // Parameterized    
        Essay(string name, int g, int s, int l, int c) : GradedActivity() {
            student = name;
            setScores(g, s, l, c);
        }

        // Mutators
        void setScores(int g, int s, int l, int c) {

            // Cap Scores
            grammar = (g < 0) ? 0 : (g > 30) ? 30 : g;
            spelling = (s < 0) ? 0 : (s > 20) ? 20 : s;
            length = (l < 0) ? 0 : (l > 20) ? 20 : l;
            content = (c < 0) ? 0 : (c > 30) ? 30 : c;
            
            calculateTotalScore();
        }
        void setStudentName(string name) {
            student = name;
        }

        // Getters
        int getGrammar() const {
            return grammar;
        }
        int getSpelling() const {
            return spelling;
        }
        int getLength() const {
            return length;
        }
        int getContent() const {
            return content;
        }
        string getStudentName() const {
            return student;
        }
};
// -------------------------------------------------------------


// Main
int main() {

    Essay ess1("John Huynh", 25, 18, 20, 28);
    
    float finalScore = ess1.getScore();
    
    // Display component scores
    cout << "Essay Score for:  " << ess1.getStudentName() << endl;
    cout << "Grammar Score:    " << ess1.getGrammar() << " / 30" << endl;
    cout << "Spelling Score:   " << ess1.getSpelling() << " / 20" << endl;
    cout << "Length Score:     " << ess1.getLength() << " / 20" << endl;
    cout << "Content Score:    " << ess1.getContent() << " / 30" << endl;
    
    // Final Score and Grade
    cout << "Total Numeric Score: " << fixed << setprecision(0) << finalScore << endl;
    cout << "Final Letter Grade:  " << ess1.getLetterGrade() << endl; // Should be 'B' (score > 79)

    // Exit stage right
    cin.get();
    return 0;
}