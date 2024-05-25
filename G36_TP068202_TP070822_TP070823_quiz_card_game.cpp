#include <iostream>
#include <fstream>
#include <string>
#include "G36_TP068202_TP070822_TP070823_Pursuit_Card_Game.hpp"
#include "G36_TP068202_TP070822_TP070823_Queue_Discarded_Cards.hpp"
#include "G36_TP068202_TP070822_TP070823_CircularQueue_Unanswered_Deck.hpp"


using namespace std; 

int main() {
	UnansweredDeckCircularQueue unansweredDeck;
	PursuitCardGame cardgame;
	cardgame.loadQuizQuestion(unansweredDeck);
	unansweredDeck.display();

	return 0;
}