#pragma once
#include <iostream> 
#include <string>

using namespace std;

struct StudentDoublyLinkedListNode {
	// Student Data
	string name;
	//string question;
	//int score;
	int totalScore;

	//link
	StudentDoublyLinkedListNode* next;
	StudentDoublyLinkedListNode* prev;
};

class studentDoublyLinkedList {
	//doublylinkedlist
	StudentDoublyLinkedListNode* head;
	StudentDoublyLinkedListNode* tail;
	int listSize;

public:
	//constructor
	studentDoublyLinkedList()
	{
		listSize = 0;
		head = tail = nullptr;
	}

	//destructor
	~studentDoublyLinkedList()
	{

	}

	StudentDoublyLinkedListNode* createNewNode(string name, int totalScore)
	{
		//create struc in heap location
		StudentDoublyLinkedListNode* newnode = new StudentDoublyLinkedListNode();

		//store info into node
		newnode->name = name;
		//newnode->question = question;
		//newnode->score = score;
		newnode->totalScore = totalScore;

		newnode->next = nullptr;
		newnode->prev = nullptr;

		return newnode;
	}

	void insertEnd(string name, int totalScore)
	{

		StudentDoublyLinkedListNode* newnode = createNewNode(name, totalScore);

		if (head == nullptr)
		{
			head = tail = newnode;
		}
		else
		{
			tail->next = newnode;
			newnode->prev = tail;
			tail = newnode;
		}
		listSize++;
	}

	void displayStudentLinkedList()
	{
		StudentDoublyLinkedListNode* current = head;

		while (current != nullptr)
		{
			cout << "StudentName: " << current->name << endl;
			//cout << current->question << endl;
			//cout << current->score << endl;
			cout << "Total Score: " << current->totalScore << endl;
			current = current->next;
		}
	}

	StudentDoublyLinkedListNode* getNodeByPostion(int number) {
		StudentDoublyLinkedListNode* current = head;
		int currentIndex = 0;
		while (current != nullptr && currentIndex < number) {
			current = current->next;
			currentIndex++;
		}
		return current;
	}

	void sort() {
		head = mergeSort(head);
		// Reset tail after sorting
		tail = head;
		if (tail) {
			while (tail->next) {
				tail = tail->next;
			}
		}
	}


private: 
	// Merge Sort Algorithm 
	StudentDoublyLinkedListNode* mergeSort(StudentDoublyLinkedListNode* node) {
		if (!node || !node->next) {
			return node;
		}

		StudentDoublyLinkedListNode* second = split(node);
		//Recur for left and right halves
		node = mergeSort(node);
		second = mergeSort(second);

		// Merge the two sorted halves
		return merge(node, second);
	}

	StudentDoublyLinkedListNode* merge(StudentDoublyLinkedListNode* first, StudentDoublyLinkedListNode* second) {
		// If first linked list is empty
		if (!first)
			return second;

		// If second linked list is empty
		if (!second)
			return first;

		// Pick the higher value for descending order
		if (first->totalScore > second->totalScore) {
			first->next = merge(first->next, second);
			first->next->prev = first;
			first->prev = nullptr;
			return first;
		}
		else {
			second->next = merge(first, second->next);
			second->next->prev = second;
			second->prev = nullptr;
			return second;
		}
	}

	StudentDoublyLinkedListNode* split(StudentDoublyLinkedListNode* head) {
		StudentDoublyLinkedListNode* fast = head;
		StudentDoublyLinkedListNode* slow = head;

		while (fast->next && fast->next->next) {
			fast = fast->next->next;
			slow = slow->next;
		}

		StudentDoublyLinkedListNode* temp = slow->next;
		slow->next = nullptr;
		return temp;
	}

};


//https://www.geeksforgeeks.org/merge-sort-for-doubly-linked-list/?ref=lbp/ (references for merge sort)