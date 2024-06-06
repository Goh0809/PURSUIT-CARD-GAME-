#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "G36_TP068202_TP070822_TP070823_CircularQueue_Unanswered_Deck.hpp"
#include "G36_TP068202_TP070822_TP070823_Stack_AnsweredDeck.hpp"
#include "G36_TP068202_TP070822_TP070823_Queue_Discarded_Cards.hpp"
#include "G36_TP068202_TP070822_TP070823_DoublyLinkedList_Student.hpp"
#include "G36_TP068202_TP070822_TP070823_BinarySearchTree_WinnerHierachyChart.h"
#include "binarytree.hpp"

using namespace std;

string studentWinner[30];

class PursuitCardGame {
	// Reminder - adjust the file path by yourself
	string quizQuestionFilePath = "C:\\Users\\Goh Ee Cheng\\Desktop\\DSTR Assignment\\DSTR Assignment\\G36_TP068202_TP070822_TP070823_quiz_question.csv";
	string studentDataFilePath = "C:\\Users\\Goh Ee Cheng\\Desktop\\DSTR Assignment\\DSTR Assignment\\G36_TP068202_TP070822_TP070823_student_data.csv";


public:
	// constructor
	PursuitCardGame() {

	}

	// load the quiz question into the unansweredDeck Queue
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

	// read the student from the csv file
	string getStudentName(int studentNum) {
		// open the file
		ifstream file(studentDataFilePath);

		// skip the header
		string header;
		getline(file, header);

		//skip the lines in the csv file until the studentNum
		string line;
		int currentLine = 1;

		while (getline(file, line)) {
			// studentNum is same with the currentLine
			if (currentLine == studentNum) {
				stringstream ss(line);
				string studentName;
				getline(ss, studentName, '\n');
				// if the student is found the file must be closed 
				file.close();
				return studentName;
			}
			currentLine++;
		}
		// close the file
		file.close();

		// if student not found return null

		return "";
	}

	// display the 3 question during each round
	void displayFirstQuestion(UnansweredDeckCircularQueue& unansweredDeck) {
		// declare a object that to receive the 
		QuizQuestion topUnansweredDeck = unansweredDeck.peek();
		string questionNumber = topUnansweredDeck.questionNumber;
		string quizQuestion = topUnansweredDeck.quizQuestion;
		string answer = topUnansweredDeck.answer;
		int score = topUnansweredDeck.score;

		cout << topUnansweredDeck.questionNumber << ". ";
		cout << topUnansweredDeck.quizQuestion << " (total score: " << score << " )" << endl << endl;
		//cout << topUnansweredDeck.answer << endl << endl;
		//cout << topUnansweredDeck.score << endl << endl;
	}

	// display the answerable discarded question
	void displaydiscardedquestion(DiscardedCardQueue& discardedcardqueue) {
		discardedCardNode* discardedCard = discardedcardqueue.peek();
		string questionNumber = discardedCard->questionNumber;
		string quizQuestion = discardedCard->quizQuestion;
		string answer = discardedCard->answer;
		int score = discardedCard->score;

		cout << questionNumber << ". ";
		cout << quizQuestion << " (total score: " << score << " )" << endl << endl;
	}
	 
	// count the total Student Num
	int countStudentAmountInStudentFile() {
		// open the file
		ifstream file(studentDataFilePath);
		 
		// skip the header line
		string header;
		getline(file, header);

		// count the student amount
		int count = 0;
		string line;

		while (getline(file, line)) {
			count++;
		}
		
		// close the file
		file.close();
		 
		// return student amount
		return count;
	}

	// insert the question answered by the student with the answer into the student daat csv file and pop the answeredDeck element out
	void deleteCurrentStudentAnsweredDeck(AnsweredDeck& answeredDeck, int totalScore, int studentNum,string studentName) {
		string processedString = processInsertedString(answeredDeck, totalScore, studentName);
		// open the csv file
		ifstream file(studentDataFilePath);
		// skip the header line
		string line;
		stringstream buffer;
		bool inserted = false;

		int currentLine = 1;
		while (getline(file, line)) {
			if (currentLine == (studentNum + 1)) {
				buffer << processedString << endl;
				inserted = true;
			}
			else {
				buffer << line << endl;
			}
			currentLine++;
		}
		if (!inserted) {
			buffer << processedString << endl;
		}

		file.close();
		// Rewrite the file with the new data
		ofstream outFile(studentDataFilePath);
		outFile << buffer.str();
		outFile.close();
	}

	// enqueue the unanawered Deck with the discarded Card
	void enqueueUnansweredDeckWithDiscardedCard(UnansweredDeckCircularQueue& unansweredDeck, DiscardedCardQueue& discardedCardQueue) {
		while (true) {
			if (discardedCardQueue.isEmpty()) {
				break;
			}
			string questionNumber = getDiscardedQuestionNumber(discardedCardQueue);
			string quizQuestion = getDiscardedQuizQuestion(discardedCardQueue);
			string answer = getDiscardedAnswer(discardedCardQueue);
			int score = getDiscardedScore(discardedCardQueue);
			discardedCardNode* discardedCard = discardedCardQueue.dequeue();
			unansweredDeck.enqueue(questionNumber, quizQuestion, answer, score);
		}
	}

	// restart the game 
	void startGame(int numStudents) {
		// open the student data csv file
		ofstream outFile(studentDataFilePath);
		// Write the header line
		outFile << "StudentName|roundOneQuestion|roundOneScore|roundTwoQuestion|roundTwoScore|roundThreeQuestion|roundThreeScore|totalScore" << endl;

		//Write student line based on the number of students
		for (int i = 1; i <= numStudents; ++i) {
			outFile << "student" << i << endl;
		}

		// close the file
		outFile.close();
	}

	// load the top 30 students to the winner binary search tree
	void insertWinnerToBST(WinnerBinarySearchTree& Winner, studentDoublyLinkedList& student) {
		for (int ranking = 0; ranking < 30; ranking++) {
			StudentDoublyLinkedListNode* current = student.getNodeByPostion(ranking);
			// insert the winner to the student winner array for display purpose
			studentWinner[ranking] = current->name;
			// insert the winner to the bst for the searching purpose
			Winner.insert(current->name, ranking);
		}
	}

	// print the winner in hierachy chart
	void printWinnerInHierachy() {
		int studentNo = 0;
		for (int i = 1; i <= 7; i++) {
			if (i != 7) {
				// add the blanket before each row to make the winner hierachy chart is showing clearly   
				for (int k = 8 - i; k > 0; k--) {
					cout << "      ";
				}
			}
			// display the winner name
			for (int j = 1; j <= i; j++) {
				if (studentNo == 30) {
					break;
				}
				cout << studentWinner[studentNo] << "  ";
				// due to there is only 30 winners in this game but following this algorithm, if proceed until 7th row
				if (j == 7) { 
					cout << studentWinner[28] << "  ";
					cout << studentWinner[29];
				}
				studentNo++;
			}
			cout << endl << endl;
		}
	}

	string getDiscardedQuestionNumber(DiscardedCardQueue& discardedcardqueue) {
		discardedCardNode* discardedCard = discardedcardqueue.peek();
		string questionNumber = discardedCard->questionNumber;
		return questionNumber;
	}

	string getDiscardedQuizQuestion(DiscardedCardQueue& discardedcardqueue) {
		discardedCardNode* discardedCard = discardedcardqueue.peek();
		string quizQuestion = discardedCard->quizQuestion;
		return quizQuestion;
	}

	string getDiscardedAnswer(DiscardedCardQueue& discardedcardqueue) {
		discardedCardNode* discardedCard = discardedcardqueue.peek();
		string answer = discardedCard->answer;
		return answer;
	}

	int getDiscardedScore(DiscardedCardQueue& discardedcardqueue) {
		discardedCardNode* discardedCard = discardedcardqueue.peek();
		int score = discardedCard->score;
		return score;
	}

private: 
	string processInsertedString(AnsweredDeck& answeredDeck,int totalScore, string studentName) {
		string insertedString = "|"+to_string(totalScore);
		while (!answeredDeck.isEmpty()) {
			Card card = answeredDeck.pop();
			stringstream ss;
			ss << "|" << card.question << "|" << card.score;
			insertedString.insert(0, ss.str());
		}
		insertedString.insert(0, studentName);
		return insertedString;
	}



};

// https://www.geeksforgeeks.org/cpp-program-to-print-pyramid-patterns/
