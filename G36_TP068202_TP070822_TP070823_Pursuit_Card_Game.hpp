#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "G36_TP068202_TP070822_TP070823_CircularQueue_Unanswered_Deck.hpp"

using namespace std;

class PursuitCardGame {
	// Reminder - adjust the file path by yourself
	string quizQuestionFilePath = "C:\\Users\\Goh Ee Cheng\\Desktop\\DSTR Assignment\\DSTR Assignment\\G36_TP068202_TP070822_TP070823_quiz_question.csv";

public:

	// constructor
	PursuitCardGame() {

	}

	void loadQuizQuestion(UnansweredDeckCircularQueue& unansweredDeck) {
		// declare the variable that corresponding to the quiz question data
		string questionNumber;
		string quizQuestion;
		string answer;
		string scoreStr;

		// open the quiz question csv file
		ifstream file(quizQuestionFilePath);

		// skip the header line
		string header;
		getline(file, header);

		// read the remaining part in the csv file and load the question into the unansweredDeck
		while (file.good()) {
			getline(file, questionNumber, '|');
			getline(file, quizQuestion, '|');
			getline(file, answer, '|');
			getline(file, scoreStr, '\n');

			// if the questionNumber equal to "" means that line be read is empty
			if (questionNumber == "") {
				break;
			}

			// convert the score to integer
			int score = stoi(scoreStr);
			// enqueue the data into the unansweredDeck queue
			unansweredDeck.enqueue(questionNumber, quizQuestion, answer, score);
		}

		// close the file
		file.close();
	}

};
