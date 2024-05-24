#pragma once
#include <iostream>
#include <string>

#define MAX_SIZE 300	// 300 quiz question is need to be provided
using namespace std;

struct QuizQuestion {
	string questionNumber;
	string quizQuestion;
	string answer;
	string score;
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
	void enqueue(string questionNumber, string quizQuestion, string answer, string score) {
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
			for (int i = front; i <= rear; i = (i + 1) % MAX_SIZE)
			{
				cout << unansweredDeck[i].questionNumber << endl;
				cout << unansweredDeck[i].quizQuestion << endl;
				cout << unansweredDeck[i].answer << endl;
				cout << unansweredDeck[i].score << endl;
			}
		}
	}



};

//https://prepinsta.com/cpp-program/circular-queue-using-array/