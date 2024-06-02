#pragma once
#include <iostream> 
#include <string>

using namespace std;

struct StudentDoublyLinkedListNode {
	// Student Data
	string name;
	string question;
	int score;
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

	StudentDoublyLinkedListNode* createNewNode(string name, string question, int score, int totalScore)
	{
		//create struc in heap location
		StudentDoublyLinkedListNode* newnode = new StudentDoublyLinkedListNode();

		//store info into node
		newnode->name = name;
		newnode->question = question;
		newnode->score = score;
		newnode->totalScore = totalScore;

		newnode->next = nullptr;
		newnode->prev = nullptr;

		return newnode;
	}

	void insertEnd(string name, string question, int score, int totalScore)
	{

		StudentDoublyLinkedListNode* newnode = createNewNode(name, question, score, totalScore);

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
			cout << current->name << endl;
			cout << current->question << endl;
			cout << current->score << endl;
			cout << current->totalScore << endl;
			current = current->next;
		}
	}
};