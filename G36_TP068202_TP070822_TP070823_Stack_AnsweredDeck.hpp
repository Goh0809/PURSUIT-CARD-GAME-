#pragma once
#include <iostream> 
#include <string>
#define size 3       // Due to there is 3 rounds only

using namespace std;

struct Card {
    string question;
    int score;
};

class AnsweredDeck {
    int top;
    Card* stack;

public:
    AnsweredDeck() {
        top = -1;
        stack = new Card[size];
    }

    ~AnsweredDeck() {
        delete[] stack;
    }

    void push(string question, int score) {
        if (top == size - 1) {
            printf("all question done");
            return;
        }
        top = top + 1;
        stack[top] = { question,score };
    }

    void pop() {
        if (top == -1) {
            printf("ans the question");
            return;
        }
        top = top - 1;
    }

    void display() {
        if (top > 0) {
            for (int i = top; i >= 0; i--) {
                Card current = stack[i];
                cout << current.question;
                cout << current.score;
            }
        }
        else {
            cout << "Stack is Empty";
        }
    }

};