#pragma once
#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#define MAX_PLAYER 100
#define MAX_COLUMN 8

using namespace std;

class Leaderboard {
    int studentAmount;
    string leaderboard[MAX_PLAYER][MAX_COLUMN];

    string studentDataFilePath = "C:\\Users\\Goh Ee Cheng\\Desktop\\DSTR Assignment\\DSTR Assignment\\G36_TP068202_TP070822_TP070823_student_data.csv";
public:

    //constructor
    Leaderboard(int studentAmount) {
        this->studentAmount = studentAmount;
    }

    void loadStudentDataToArray() {
        string studentName;
        string roundOneQuestion, roundTwoQuestion, roundThreeQuestion;
        string roundOneScore, roundTwoScore, roundThreeScore, totalScore;

        //open studentdata csv file
        ifstream file(studentDataFilePath);

        //skip header
        string header;
        getline(file, header);

        int row = 0;

        //read data in csv file and load into the 2d array
        while (file.good() && row < studentAmount) {
            getline(file, studentName, '|');
            getline(file, roundOneQuestion, '|');
            getline(file, roundOneScore, '|');
            getline(file, roundTwoQuestion, '|');
            getline(file, roundTwoScore, '|');
            getline(file, roundThreeQuestion, '|');
            getline(file, roundThreeScore, '|');
            getline(file, totalScore, '\n');

            // if the studentName equal to "" means that line be read is empty
            if (studentName == "") {
                break;
            }

            // assign the value into the array
            leaderboard[row][0] = studentName;
            leaderboard[row][1] = roundOneQuestion;
            leaderboard[row][2] = roundOneScore;
            leaderboard[row][3] = roundTwoQuestion;
            leaderboard[row][4] = roundTwoScore;
            leaderboard[row][5] = roundThreeQuestion;
            leaderboard[row][6] = roundThreeScore;
            leaderboard[row][7] = totalScore;
            
            
            row++;
        }
        file.close();
    }

    // linear search - O(n)
    void search(string studentName) {
        for (int i = 0; i < studentAmount; i++) {
            if (leaderboard[i][0] == studentName) {
                cout << "Ranking: " << i+1 << endl;
                cout << leaderboard[i][0] << ": " << endl;
                string round1Data = leaderboard[i][1].substr(0, leaderboard[i][1].find('?')) + "? " + "Score: " + leaderboard[i][2];
                cout << "Round1: " << round1Data << endl;
                string round2Data = leaderboard[i][3].substr(0, leaderboard[i][1].find('?')) + "? " + "Score: " + leaderboard[i][4];
                cout << "Round2: " << round2Data << endl;
                string round3Data = leaderboard[i][5].substr(0, leaderboard[i][1].find('?')) + "? " + "Score: " + leaderboard[i][6];
                cout << "Round3: " << round3Data << endl;
                cout << "Total Score: " << leaderboard[i][7] << endl;
                return; 
            }
        }
        cout << "Student is not found" << endl;
    }

    void displayDescending() {
        cout << "leaderboard: " << endl;
        cout << "Ranking" << setw(15) << "StudentName" << setw(20) << "Question" << setw(52) << "Score" << setw(15) << "Total Score" << endl;
        cout << "---------------------------------------------------------------------------------------------------------------" << endl;
        for (int i = 0; i < studentAmount; i++) {
            string space;
            if (leaderboard[i][0].length() == 9) {
                space = "          ";
            }
            else {
                space = "           ";
            }
            cout << i + 1 << "         " << leaderboard[i][0] << space; // Print student number and name

            // Process round 1 questions
            string round1Question = leaderboard[i][1];
            cout << round1Question.substr(0, 50) << "           " << leaderboard[i][2] << "          " << leaderboard[i][7] << endl;

            // Output round 1 questions
            for (int j = 50; j < round1Question.length(); j += 50) {
                cout << "                             " << round1Question.substr(j, 50) << endl;
            }
            cout << endl;
            // Process round 2 questions
            string round2Question = leaderboard[i][3];
            cout << "                             " << round2Question.substr(0, 50) << "           " << leaderboard[i][4] << endl;

            // Output round 2 questions
            for (int k = 50; k < round2Question.length(); k += 50) {
                cout << "                             " << round2Question.substr(k, 50) << endl;
            }
            cout << endl;
            // Process round 3 questions
            string round3Question = leaderboard[i][5];
            cout << "                             " << round3Question.substr(0, 50) << "           " << leaderboard[i][6] << endl;

            // Output round 3 questions
            for (int l = 50; l < round3Question.length(); l += 50) {
                cout << "                             " << round3Question.substr(l, 50) << endl;
            }

            cout << "---------------------------------------------------------------------------------------------------------------" << endl;
        }
    }

    void displayAscending() {
        cout << "leaderboard: " << endl;
        cout << "Ranking" << setw(15) << "StudentName" << setw(20) << "Question" << setw(52) << "Score" << setw(15) << "Total Score" << endl;
        cout << "---------------------------------------------------------------------------------------------------------------" << endl;
        for (int i = studentAmount - 1; i >= 0; i--) {
            string space;
            if (leaderboard[i][0].length() == 9) {
                space = "          ";
            }
            else {
                space = "           ";
            }
            cout << i + 1 << "         " << leaderboard[i][0] << space; // Print student number and name
            
            // Process round 1 questions
            string round1Question = leaderboard[i][1];
            cout << round1Question.substr(0, 50) << "           " << leaderboard[i][2] << "          " << leaderboard[i][7] << endl;

            // Output round 1 questions
            for (int j = 50; j < round1Question.length(); j += 50) {
                cout << "                             " << round1Question.substr(j, 50) << endl;
            }
            cout << endl;
            // Process round 2 questions
            string round2Question = leaderboard[i][3];
            cout << "                             " << round2Question.substr(0, 50) << "           " << leaderboard[i][4] << endl;

            // Output round 2 questions
            for (int k = 50; k < round2Question.length(); k += 50) {
                cout << "                             " << round2Question.substr(k, 50) << endl;
            }
            cout << endl;
            // Process round 3 questions
            string round3Question = leaderboard[i][5];
            cout << "                             " << round3Question.substr(0, 50) << "           " << leaderboard[i][6] << endl;

            // Output round 3 questions
            for (int l = 50; l < round3Question.length(); l += 50) {
                cout << "                             " << round3Question.substr(l, 50) << endl;
            }

            cout << "---------------------------------------------------------------------------------------------------------------" << endl;
        }


    }
    

    // bubble sort O (n) 
    void sortDescending() {
        for (int round = 1; round <= studentAmount; round++) {
            bool swapresult = false;
            for (int j = 0; j < studentAmount - 1; j++) {
                if (atoi(leaderboard[j][7].c_str()) < atoi(leaderboard[j + 1][7].c_str())) {
                    // Swap the rows
                    for (int k = 0; k < MAX_COLUMN; ++k) {
                        swap(leaderboard[j][k], leaderboard[j + 1][k]);
                        swapresult = true;
                    }
                }
            }
        }
    }


};
