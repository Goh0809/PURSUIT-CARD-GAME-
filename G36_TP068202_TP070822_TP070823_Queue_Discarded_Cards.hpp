#pragma once
#include <iostream> 
#include <string>

using namespace std;

// discarded card node 
struct discardedCardNode {
	// question data
	string questionNumber;
	string quizQuestion;
	string answer;
	int score;

	// link
	discardedCardNode* nextAdd;
};

class DiscardedCardQueue {
	discardedCardNode* front;
	discardedCardNode* rear;
	int queueSize;

public:
	// constructor 
	DiscardedCardQueue() {
		front = nullptr;
		rear = nullptr;
		queueSize = 0;
	}

	// destructor
	~DiscardedCardQueue() {

	}

	bool isEmpty() {
		if (front == nullptr)
			return true;
		return false;
	}

	int getSize() {
		return queueSize;
	}

	// create new node for discarded card queue
	discardedCardNode* createNewNode(string questionNumber, string quizQuestion, string answer, int score) {
		// create struct in heap location
		discardedCardNode* newNode = new discardedCardNode();

		// store the question detail inside the new node
		newNode->questionNumber = questionNumber;
		newNode->quizQuestion = quizQuestion;
		newNode->answer = answer;
		newNode->score = score;

		newNode->nextAdd = nullptr;

		return newNode;
	}

	// enqueue
	void enqueue(string questionNumber, string quizQuestion, string answer, int score) {
		discardedCardNode* newNode = createNewNode(questionNumber, quizQuestion, answer, score);
		if (front == nullptr) {
			front = rear = newNode;
		}
		else {
			rear->nextAdd = newNode;
			rear = newNode;
		}
		queueSize++;
	}

	// dequeue
	discardedCardNode* dequeue() {
		discardedCardNode* node = front;
		if (isEmpty()) {
			cout << "Queue is empty, unable to dequeue!" << endl;
			return nullptr;
		}
		discardedCardNode* current = front;
		front = front->nextAdd;
		if (front == nullptr) 
			rear = nullptr;
		delete current;
		queueSize--;
		return node;

	}

	// peek
	discardedCardNode* peek() {
		if (isEmpty()) {
			cout << "Queue is empty, unable to peek!" << endl;
			return nullptr;
		}
		return front;

	}

	void display() {
		discardedCardNode* current = front;
		while (current != nullptr) {
			cout << current->questionNumber << endl;
			cout << current->quizQuestion << endl;
			cout << current->answer;
			cout << current->score;
			current = current->nextAdd;
		}
		cout << endl;
	}
};