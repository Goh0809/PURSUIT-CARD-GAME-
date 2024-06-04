#pragma once
#include <iostream> 
#include <string>
#define SIZE 3       // Due to there is 3 rounds only

using namespace std;

struct Card {
    string question;
    int score;
};

class AnsweredDeck {
    int top;
    Card* stack;

public:
    // constructor
    AnsweredDeck() {
        top = -1;
        stack = new Card[SIZE];
    }

    // destructur
    ~AnsweredDeck() {
        delete[] stack;
    }

    // determine the stack is empty or not
    bool isEmpty() {
        return (top == -1);
    }

    // determine the stack is full or not
    bool isFull() {
        return (top == (SIZE - 1));
    }

    // push the answered question and its score inside the stack
    void push(string question, int score) {
        if (isFull()) {
            cout << "You have completed the quiz";
            return;
        }
        top += 1;
        stack[top] = { question,score };
    }

    // pop the first element in the stack
    Card pop() {
        if (isEmpty()) {
            cout << "Stack underflow";
            return Card();
        }
        Card current = stack[top--];
        return current;
    }

    Card peek() {
        return stack[top];
    }

    void display() {
        if (top > 0) {
            for (int i = top; i >= 0; i--) {
                Card current = stack[i];
                cout << current.question<<endl;
                cout << current.score<<endl;
            }
        }
        else {
            cout << "Stack is Empty";
        }
    }

};