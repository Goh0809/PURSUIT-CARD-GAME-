#pragma once
#include <iostream> 
#include <string>

using namespace std;

struct discardedCardQueueNode {
	// question data
	int questionNumber;
	/*string quizQuestion;
	char answer;*/

	// link
	discardedCardQueueNode* next; 
	discardedCardQueueNode* prev;
};

class DiscardedCardQueue {
	discardedCardQueueNode* discardedCardQueueFront;
	discardedCardQueueNode* discardedCardQueueRear;
	int discardedCardQueueSize;

public:
	// constructor
	DiscardedCardQueue() {
		discardedCardQueueFront = nullptr;
		discardedCardQueueRear = nullptr;
		discardedCardQueueSize = 0;
	}

	// destructor
	~DiscardedCardQueue() {
		
	}

	// get the size of discarded card queue
	int getSize() {
		return discardedCardQueueSize;
	}

	// determine whether the discarded card queue is empty 
	bool isEmpty() {
		return discardedCardQueueSize == 0;
	}

	// Create new node for discarded card queue
	discardedCardQueueNode* createNewNode(int questionNumber) {
		// create struct in heap location
		discardedCardQueueNode* newNode = new discardedCardQueueNode;
		
		// put all the details into the location
		newNode->questionNumber = questionNumber;
		/*newNode->quizQuestion = quizQuestion;
		newNode->answer = answer;*/
		newNode->next = nullptr;
		newNode->prev = nullptr;

		return newNode;
	}

	// enqueue
	void enqueue(int questionNumber) {
		discardedCardQueueNode* newNode = createNewNode(questionNumber);
		if (isEmpty()) {
			discardedCardQueueFront = discardedCardQueueRear = newNode;
		}
		else {
			discardedCardQueueRear->next = newNode;
			newNode->prev = discardedCardQueueRear;
			discardedCardQueueRear = newNode;
		}
		discardedCardQueueSize++;
	}

	// dequeue
	void dequeue() {
		if (isEmpty()) {
			throw out_of_range("Queue is Empty");
		} 
		discardedCardQueueNode* temp = discardedCardQueueFront;
		discardedCardQueueFront = discardedCardQueueFront->next;
		if (discardedCardQueueFront == nullptr) {
			discardedCardQueueRear = nullptr;
		}
		else {
			discardedCardQueueFront->prev = nullptr;
		}
		delete temp;
		discardedCardQueueSize--;
	}

	// display the node of discarded card queue - testing
	void dispalyFromFront() {
		discardedCardQueueNode* current = discardedCardQueueFront;
		while (current != nullptr) {
			cout << current->questionNumber << " ";
			current = current->next;
		}
	}

};