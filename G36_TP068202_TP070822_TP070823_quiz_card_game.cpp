#include <iostream>
#include <fstream>
#include <string>
#include "G36_TP068202_TP070822_TP070823_Queue_Discarded_Cards.hpp"
#include "G36_TP068202_TP070822_TP070823_CircularQueue_Unanswered_Deck.hpp"


using namespace std; 

int main() {
	// string to integer - stoi(str)
	//DiscardedCardQueue dc;
	//dc.enqueue("1", "What is Your Name", "B", "10");
	//dc.enqueue("2", "What is Your Age", "C", "15");
	//dc.dequeue();
	//dc.display();
	UnansweredDeckCircularQueue ud;
	ud.enqueue("1", "What is Your Name", "B", "10");
	ud.enqueue("2", "What is Your Age", "C", "15");
	ud.display();
	ud.dequeue();
	ud.display();
	ud.dequeue();
	ud.display();
	return 0;
}