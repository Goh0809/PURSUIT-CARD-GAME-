#include <string>
#include <cstdlib>
#include "G36_TP068202_TP070822_TP070823_Pursuit_Card_Game.hpp"
#include "G36_TP068202_TP070822_TP070823_Queue_Discarded_Cards.hpp"
#include "G36_TP068202_TP070822_TP070823_CircularQueue_Unanswered_Deck.hpp"
#include "G36_TP068202_TP070822_TP070823_Stack_AnsweredDeck.hpp"
#include "G36_TP068202_TP070822_TP070823_DoublyLinkedList_Student.hpp"
#include "G36_TP068202_TP070822_TP070823_BinarySearchTree_WinnerHierachyChart.h"

using namespace std; 

// declare necessary object
PursuitCardGame cardGame;
UnansweredDeckCircularQueue unansweredDeck;
studentDoublyLinkedList student;
AnsweredDeck answeredDeck;
DiscardedCardQueue discardedCard;
WinnerBinarySearchTree winner;

void manualGameMode(int studentNum);
void autoGameMode(int studentNum);

int main() {

	

	cout << "Welcome to Pursuit Card Game!" << endl;
	// start the Pursuit Card Game by entering the number of students
	int studentAmount;
	cout << "Enter the amount of student" << endl;
	cin >> studentAmount;
	cardGame.startGame(studentAmount);

	// declare the necessary global variable
	int studentNum = 1;

	// Preparation Step
	// 1. Call the method within the PursuitCardGame class to load the question inside the unanswered deck
	cardGame.loadQuizQuestion(unansweredDeck);
	// 2. randomize the question
	unansweredDeck.randomize();

	int gameMode;
	cout << "Enter 1 to Begin the Pursuit Card Game with Manual Mode" << endl << "Enter 2 to Begin the Pursuit Card Game with Auto Testing Mode" << endl << "Enter your selection: " << endl;
	cin >> gameMode;

	// initiate Game
	if (gameMode == 1) {
		// call manual game mode method
		manualGameMode(studentNum);
	}
	else if (gameMode == 2) {
		// call auto testing mode method
		autoGameMode(studentNum);
	}

	// sort the student descending by the total score to rank them
	student.sort();
	// call the method to insert top 30 student into the winner bst
	cardGame.insertWinnerToBST(winner, student);
	string searchStudent;
	cin >> searchStudent;
	if (winner.find(searchStudent)) {
		cout << "found";
	}




	// testing
	// ask to restart the game or exit the game
	int exit;
	cout << "Type 1 to restart the game" << endl << "Type 2 to end the game" << endl << "Enter your decision: " << endl;
	cin >> exit;
	if (exit == 1) {
		cout << "Enter the amount of studednt" << endl;
		cin >> studentAmount;
		cardGame.startGame(studentAmount);
	}
	else if (exit == 2) {
		cardGame.startGame(studentAmount);
		system("exit");
	}

	return 0;
}

void manualGameMode(int studentNum) {
	// inititate the pursuit card game - manual mode
	while (studentNum <= cardGame.countStudentAmountInStudentFile()) {
		// get the student name first
		string studentName = cardGame.getStudentName(studentNum);
		cout << studentName << ":" << endl;
		// due to there is 3 round per student
		int round = 1;
		// initiate the total score varaible to calculate the total score of the student
		int totalScore = 0;
		while (round <= 3) {
			cout << "Round " << round << ":" << endl;
			// peek the answer of the question
			cardGame.displayFirstQuestion(unansweredDeck);

			// display the first question means dequeue the question also
			QuizQuestion currentQuestion = unansweredDeck.peek();
			string questionNumber = currentQuestion.questionNumber;
			string quizQuestion = currentQuestion.quizQuestion;
			string questionAnswer = currentQuestion.answer;
			int score = currentQuestion.score;

			// ask the student to select whether they want to answer the current question or discarded the question
			int selection;
			cout << "Select 1 to answer the question" << endl << "Select 2 to discard the question" << endl << "Select 3 to answer the discarded question" << endl << "Enter your selection: " << endl;
			cin >> selection;
			cout << endl;
			if (selection == 1) {
				// start answering the question
				string answer;
				cout << "Answer the Question: ";
				cin >> answer;
				cout << endl;
				// check wheter the answer is correct or not
				unansweredDeck.dequeue();
				if (answer == questionAnswer) {
					// once answer the correct answer, push the quizQuestion with the score gained by the student into the answeredDeck
					answeredDeck.push(currentQuestion.quizQuestion, score);
					totalScore += score;
					cout << endl;
				}
				else {
					// if the answer is not correct, push the quizQuestion as well but the score is 0
					answeredDeck.push(currentQuestion.quizQuestion, 0);
				}
				round++;
			}
			else if (selection == 2) {
				// start discarded Question Logic
				discardedCard.enqueue(questionNumber, quizQuestion, questionAnswer, score);
				unansweredDeck.dequeue();
			}
			else if (selection == 3) {
				if (discardedCard.isEmpty()) {
					continue;
				}
				cardGame.displaydiscardedquestion(discardedCard);
				string discardedAnswer;
				cout << "Answer the Question or Type 1 to Continue Answer the Other Question: " << endl;

				cin.ignore();
				getline(cin, discardedAnswer);

				string discardedQuestionNumber = cardGame.getDiscardedQuestionNumber(discardedCard);
				string discardedQuizQuestion = cardGame.getDiscardedQuizQuestion(discardedCard);
				string discardedQuestionAnswer = cardGame.getDiscardedAnswer(discardedCard);
				int discardedQuestionScore = cardGame.getDiscardedScore(discardedCard);
				discardedCard.dequeue();

				if (discardedAnswer == discardedQuestionAnswer) {
					// once answer the correct answer, push the quizQuestion with the score gained by the student into the answeredDeck
					answeredDeck.push(discardedQuizQuestion, score * 0.8);
					totalScore += (score * 0.8);
					cout << endl;
				}
				else {
					// if the answer is not correct, push the quizQuestion as well but the score is 0
					answeredDeck.push(discardedQuizQuestion, 0);
				}
				round++;
			}
		}
		// after third round per student end the pursuit card game should dequeue the discardedQuestion and enqueue into the unansweredDesk again to keep the balance
		if (discardedCard.isEmpty()) {

		}
		else {
			cardGame.enqueueUnansweredDeckWithDiscardedCard(unansweredDeck, discardedCard);
		}
		// after complete the three round store the student data inside the student doubly linked list
		student.insertEnd(studentName, totalScore);
		// call the method to write the data inside the csv file
		cardGame.deleteCurrentStudentAnsweredDeck(answeredDeck, totalScore, studentNum, studentName);
		// clean the command prompt screen to initiate next student round
		system("cls");
		// proceed to next student
		studentNum++;
	}
}
void autoGameMode(int studentNum) {
	// inititate the pursuit card game - auto mode (system will load the answer automatically)
	while (studentNum <= cardGame.countStudentAmountInStudentFile()) {
		// get the student name first
		string studentName = cardGame.getStudentName(studentNum);
		cout << studentName << ":" << endl;
		// due to there is 3 round per student
		int round = 1;
		// initiate the total score varaible to calculate the total score of the student
		int totalScore = 0;
		while (round <= 3) {
			cout << "Round " << round << ":" << endl;
			// peek the answer of the question
			cardGame.displayFirstQuestion(unansweredDeck);

			// display the first question means dequeue the question also
			QuizQuestion currentQuestion = unansweredDeck.peek();
			string questionNumber = currentQuestion.questionNumber;
			string quizQuestion = currentQuestion.quizQuestion;
			string questionAnswer = currentQuestion.answer;
			int score = currentQuestion.score;

			// ask the student to select whether they want to answer the current question or discarded the question
			int selection;
			cout << "Select 1 to answer the question" << endl << "Select 2 to discard the question" << endl << "Select 3 to answer the discarded question" << endl << "Enter your selection: " << endl;
			selection = 1;
			cout << endl;
			if (selection == 1) {
				// start answering the question
				string answer;
				cout << "Answer the Question: ";
				answer = "A";
				cout << endl;
				// check wheter the answer is correct or not
				unansweredDeck.dequeue();
				if (answer == questionAnswer) {
					// once answer the correct answer, push the quizQuestion with the score gained by the student into the answeredDeck
					answeredDeck.push(currentQuestion.quizQuestion, score);
					totalScore += score;
					cout << endl;
				}
				else {
					// if the answer is not correct, push the quizQuestion as well but the score is 0
					answeredDeck.push(currentQuestion.quizQuestion, 0);
				}
				round++;
			}
		}
		// after complete the three round store the student data inside the student doubly linked list
		student.insertEnd(studentName, totalScore);
		// call the method to write the data inside the csv file
		cardGame.deleteCurrentStudentAnsweredDeck(answeredDeck, totalScore, studentNum, studentName);
		// clean the command prompt screen to initiate next student round
		system("cls");
		// proceed to next student
		studentNum++;
		cout << "Data Loading Complete";
		cout << endl;
	}
}