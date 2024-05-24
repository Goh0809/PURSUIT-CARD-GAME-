#pragma once
#include <iostream> 
#include <string>

using namespace std;

// discarded card node 
struct discardedCardQueueNode {
	// question data
	string questionNumber;
	string quizQuestion;
	string answer;
	string score;

	// link
	discardedCardQueueNode* nextAdd;
};

class DiscardedCardQueue {
	discardedCardQueueNode* discardedCardQueueFront;
	discardedCardQueueNode* discardedCardQueueRear;
	int discardedCardQueueSize;

public:
	// constructor 
	DiscardedCardQueue() {
		discardedCardQueueFront = discardedCardQueueRear = nullptr;
		discardedCardQueueSize = 0;
	}

	// destructor
	~DiscardedCardQueue() {

	}

	bool isEmpty() {
		if (discardedCardQueueFront == nullptr)
			return true;
		return false;
	}

	int getSize() {
		return discardedCardQueueSize;
	}

	// create new node for discarded card queue
	discardedCardQueueNode* createNewNode(string questionNumber, string quizQuestion, string answer, string score) {
		// create struct in heap location
		discardedCardQueueNode* newNode = new discardedCardQueueNode();

		// store the question detail inside the new node
		newNode->questionNumber = questionNumber;
		newNode->quizQuestion = quizQuestion;
		newNode->answer = answer;
		newNode->score = score;

		newNode->nextAdd = nullptr;

		return newNode;
	}

	// enqueue
	void enqueue(string questionNumber, string quizQuestion, string answer, string score) {
		discardedCardQueueNode* newNode = createNewNode(questionNumber, quizQuestion, answer, score);
		if (discardedCardQueueFront == nullptr) {
			discardedCardQueueFront = discardedCardQueueRear = newNode;
		}
		else {
			discardedCardQueueRear->nextAdd = newNode;
			discardedCardQueueRear = newNode;
		}
		discardedCardQueueSize++;
	}

	// dequeue
	discardedCardQueueNode* dequeue() {
		discardedCardQueueNode* node = discardedCardQueueFront;
		if (isEmpty()) {
			cout << "Queue is empty, unable to delete!" << endl;
			exit(1);
		}
		discardedCardQueueNode* current = discardedCardQueueFront;
		discardedCardQueueFront = discardedCardQueueFront->nextAdd;
		if (discardedCardQueueFront == nullptr) 
			discardedCardQueueRear = nullptr;
		delete current;
		discardedCardQueueSize--;
		return node;

	}

	// peek
	discardedCardQueueNode* peek() {
		if (isEmpty()) {
			cout << "Queue is empty, unable to delete!" << endl;
			exit(1);
		}
		return discardedCardQueueFront;

	}

	void displayQueue() {
		discardedCardQueueNode* current = discardedCardQueueFront;
		while (current != nullptr) {
			current = current->nextAdd;
		}
		cout << endl;
	}





};