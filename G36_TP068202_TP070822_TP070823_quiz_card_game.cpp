#include <iostream>
#include <fstream>
#include <string>
#include "G36_TP068202_TP070822_TP070823_Pursuit_Card_Game.hpp"
#include "G36_TP068202_TP070822_TP070823_Queue_Discarded_Cards.hpp"
#include "G36_TP068202_TP070822_TP070823_CircularQueue_Unanswered_Deck.hpp"
#include "G36_TP068202_TP070822_TP070823_Stack_AnsweredDeck.hpp"


using namespace std; 

int main() {
	AnsweredDeck ad;
	ad.push("What is your name", 10);
	ad.push("What is your hobby", 8);
	ad.display();


	return 0;
}