#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#define MAX_SIZE 300	// 300 quiz question is need to be provided
using namespace std;

struct QuizQuestion {
	string questionNumber;
	string quizQuestion;
	string answer;
	int score;
};

class UnansweredDeckCircularQueue {
	int front;
	int rear;
	QuizQuestion* unansweredDeck;

public:
	// constructor
	UnansweredDeckCircularQueue() {
		front = -1;
		rear = -1;
		unansweredDeck = new QuizQuestion[MAX_SIZE];
	}
	
	// destructor
	~UnansweredDeckCircularQueue() {
		delete[] unansweredDeck;
	}

	// check if the queue is empty
	bool isEmpty() {
		if (front == -1)
			return true;
		return false;
	}

	// check if the queue is full
	bool isFull() {
		if ((front == 0 && rear == MAX_SIZE - 1) || ((rear + 1) % MAX_SIZE == front)) {
			return true;
		}
		return false;
	}

	// enqueue
	void enqueue(string questionNumber, string quizQuestion, string answer, int score) {
		if (isFull()) {
			cout << "Queue is Full, Unable to Enqueue!";
			return;
		}
		else if (isEmpty()) {
			front++;
		}
		rear = (rear + 1) % MAX_SIZE;
		unansweredDeck[rear] = { questionNumber, quizQuestion, answer, score };
	}

	// dequeue
	QuizQuestion dequeue() {
		if (isEmpty()) {
			cout << "Queue is empty, Unable to dequeue!";
			return QuizQuestion();
		}
		QuizQuestion temp = unansweredDeck[front];
		if (front == rear) {
			front = rear = -1;
		}
		else {
			front = (front + 1) % MAX_SIZE;
		}
		return temp;
	}

	// peek
	QuizQuestion peek() {
		if (isEmpty()) {
			cout << "Queue is Empty, Unable to Peek!" << endl;
			return QuizQuestion();
		}
		return unansweredDeck[front];
	}


	// display
	void display() {
		if (isEmpty()) {
			cout << "Queue is Empty, Nothing to Display!" << endl;
			return;
		} 
		else {
			int i;
			for (i = front; i != rear; i = (i + 1) % MAX_SIZE)
			{
				cout << unansweredDeck[i].questionNumber << endl;
				cout << unansweredDeck[i].quizQuestion << endl;
				cout << unansweredDeck[i].answer << endl;
				cout << unansweredDeck[i].score << endl << endl;
			}
			cout << unansweredDeck[i].questionNumber << endl;
			cout << unansweredDeck[i].quizQuestion << endl;
			cout << unansweredDeck[i].answer << endl;
			cout << unansweredDeck[i].score << endl << endl;
		}
	}

	// Fisher–Yates shuffle Algorithm to randomize the array
	void randomize() {
		srand(time(NULL));
		for (int i = MAX_SIZE - 1; i > 0; i--) {
			int j = rand() % (i + 1);
			swap(&unansweredDeck[i], &unansweredDeck[j]);
		}
	}

private: 
	void swap(QuizQuestion *a, QuizQuestion* b) {
		QuizQuestion temp = *a;
		*a = *b;
		*b = temp;
	}

};

//https://prepinsta.com/cpp-program/circular-queue-using-array/
//https://www.geeksforgeeks.org/shuffle-a-given-array-using-fisher-yates-shuffle-algorithm/