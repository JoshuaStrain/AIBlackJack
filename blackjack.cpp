//COSC 4368 AI
//Final Project
//Mike Schulenberg 1409566
//Joshua Strain 1332695
//Nick Biddle 0185799
//
//Blackjack game


#include <iostream>
#include <string>
#include <ctime>
#include <vector>
using namespace std;


const int RANDMAX = 32767;

class deck {
public:
	deck();
	~deck();
	int deckSize = 52;
	bool cardState[52];

	char *cardNum[13] = { "2","3","4","5","6","7","8","9","10","Jack","Queen","King","Ace" };
	char *suit[4] = { "Clubs","Diamonds","Spades","Hearts" };

	void printDeck();
};

struct card {
	int cardNumber;
	int cardSuit;
	void printCard(deck d);

};

deck::deck() {
	for (int i = 0; i < 52; i++) {
		cardState[i] = true;
	}
}

deck::~deck() {}

void card::printCard(deck d) {
	cout << "The " << d.cardNum[cardNumber] << " of " << d.suit[cardSuit] << ",  ";
}

void deck::printDeck() {
	cout << "*****************DECK STATE******************" << endl;
	for (int i = 0; i < 52; i++) {
		cout << "index:  " << i + 1 << "\tcard state:  " << cardState[i] << endl;
	}
}

void seed() {
	time_t tTime;
	time(&tTime);
	srand(tTime);
	rand();
}

void dealHand(vector<card> &hand, deck &d) {
	int count = 0;
	//int cardIndex;

	for (int i = 0; i < 2; i++) {
		//random card with number between 0 and 51
		//int r = (int)(1.0 * rand() / (RAND_MAX + 1) * d.deckSize);
		int r = (int)(1.0 * rand() / (RANDMAX + 1) * d.deckSize);

		//skip previously selected cards
		while (!d.cardState[r]) {
			r = (int)(1.0 * rand() / (RANDMAX + 1) * d.deckSize);
		}

		d.deckSize--;
		d.cardState[r] = false;
		int n = r % 13;
		int s = r / 13;
		//cout << "random num:  " << r << "\tcard index:  " << cardIndex << "\tcard num:  " << n << "\tsuit:  " << s << endl;

		struct card c;
		c.cardNumber = n;
		c.cardSuit = s;

		hand.push_back(c);
	}
}

void printHand(vector<card> &hand, deck &d, int handSize) {

	cout << endl << "***************************" << endl;
	cout << "       PLAYER  HAND        " << endl;
	for (int i = 0; i < handSize; i++) {
		hand[i].printCard(d);
	}
	cout << endl;
}

void printComputerHand(vector<card> &hand, deck &d, int handSize) {

	cout << endl << "***************************" << endl;
	cout << "      COMPUTER  HAND       " << endl;
	for (int i = 0; i < handSize; i++) {
		hand[i].printCard(d);
	}
	cout << endl;
}

//calculate teh score of the current hand with aces.  Aces can be 1 or 11, so the 
//best score is selected.
int scoreWithoutAces(vector<card> &hand, deck &d, int handSize) {
	int score = 0;
	for (int i = 0; i < handSize; i++) {
		int value;
		char *cardVal = d.cardNum[hand[i].cardNumber];
		if (cardVal == "2" || cardVal == "3" || cardVal == "4" || cardVal == "5" || cardVal == "6" || cardVal == "7" || cardVal == "8" || cardVal == "9") {
			value = *cardVal - '0';
			cout << "value = " << value << endl;
			score += value;
		}
		else if (cardVal == "10" || cardVal == "Jack" || cardVal == "Queen" || cardVal == "King") {
			value = 10;
			cout << "value = " << value << endl;
			score += value;
		}
		else if (cardVal == "Ace") {
			continue;
		}
	}
	return score;
}

//calculate the score of any number of face cards
int scoreWithAces(vector<card> &hand, deck &d, int handSize, int &score) {
	for (int i = 0; i < handSize; i++) {
		char *cardVal = d.cardNum[hand[i].cardNumber];

		if (cardVal == "Ace") {
			if (score + 11 <= 21) {
				cout << "this ace is worth 11" << endl;
				score += 11;
			}
			else {
				cout << "this ace is worth 1" << endl;
				score += 1;
			}
		}
	}
	return score;
}

//calculate the total hand score
int handScore(vector<card> &hand, deck &d, int handSize) {
	int score = scoreWithoutAces(hand, d, handSize);
	int totalScore = scoreWithAces(hand, d, handSize, score);
	cout << "total hand score: " << totalScore << endl;
	cout << endl << "***************************" << endl << endl;
	return totalScore;
}

void hit(vector<card> &hand, deck &d, int &handSize) {

	//deal cardhandScore
	int r = (int)(1.0 * rand() / (RANDMAX + 1) * d.deckSize);
	//if card has been dealt previously, skip it
	while (!d.cardState[r]) {
		r = (int)(1.0 * rand() / (RANDMAX + 1) * d.deckSize);
	}
	//int count = 0;

	d.deckSize--;
	handSize++;
	d.cardState[r] = false;
	int n = r % 13;
	int s = r / 13;
	//cout << "random num:  " << r << "\tcard index:  " << cardIndex << "\tcard num:  " << n << "\tsuit:  " << s << endl;

	struct card c;
	c.cardNumber = n;
	c.cardSuit = s;

	hand.push_back(c);
}



void split(vector<card> &hand, vector<card> &hand1, vector<card> &hand2) {
	hand1.push_back(hand[0]);
	hand2.push_back(hand[1]);
}

void checkScores(int playerScore, int computerScore) {
	//if neither bust
	if (playerScore <= 21 && computerScore <= 21) {
		if (computerScore > playerScore) {
			cout << "Computer has a score of " << computerScore << endl;
			cout << "Player has a score of " << playerScore << endl;
			cout << "Computer wins!" << endl;
		}
		else if (computerScore < playerScore) {
			cout << "Player has a score of " << playerScore << endl;
			cout << "Computer has a score of " << computerScore << endl;
			cout << "Player wins!" << endl;
		}
		else if (computerScore == playerScore) {
			cout << "Player has a score of " << playerScore << endl;
			cout << "Computer has a score of " << computerScore << endl;
			cout << "Result is a push" << endl;
		}
	}
	//if either busts
	else if (playerScore > 21 && computerScore <= 21) {
		cout << "Player Busted" << endl;
		cout << "Computer wins!" << endl;
	}
	else if (playerScore <= 21 && computerScore > 21) {
		cout << "Computer Busted" << endl;
		cout << "Player wins!" << endl;
	}
	//if both bust
	else if (playerScore > 21 && computerScore > 21) {
		cout << "Both Busted" << endl;
		cout << "result is a push" << endl;
	}
}

//This is where the tree is implemented
int decide(vector<card> &playerHand, vector<card> &computerHand, deck &d, int playerHandSize, int computerHandSize, bool initialComputerHand) {
	//0 for hit, 1 for stand, and 2 for split

	char *compCard1Val = d.cardNum[computerHand[0].cardNumber];
	char *compCard2Val = d.cardNum[computerHand[1].cardNumber];

	//tree root.  If hand is splittable do...
	if (initialComputerHand && compCard1Val == compCard2Val) {
		//always split pairs of aces and pairs of 8's
		if (compCard1Val == "Ace" || compCard1Val == "8") {
			return 2;
		}
		//never split, always stand with any pair of 10 value cards
		else if (compCard1Val == "10" || compCard1Val == "Jack" || compCard1Val == "Queen" || compCard1Val == "King") {
			return 1;
		}
		//never split, always hit with a pair of 4s or 5s
		else if (compCard1Val == "4" || compCard1Val == "5") {
			return 0;
		}
		//split 9s only if other player has certain cards
		else if (compCard1Val == "9") {
			for (int i = 0; i < playerHandSize; i++) {
				//only split 9s if opponent has a 2,3,4,5,6,8, or 9
				char *playerCardValue = d.cardNum[playerHand[0].cardNumber];
				if (playerCardValue == "2" || playerCardValue == "3" || playerCardValue == "4" || playerCardValue == "5" || playerCardValue == "6" || playerCardValue == "8" || playerCardValue == "9") {
					return 2;
				}
			}
			//if opponent doesnt have any appropriate cards, then stand
			return 1;
		}
		//split 9s only if other player has certain cards
		else if (compCard1Val == "6") {
			for (int i = 0; i < playerHandSize; i++) {
				char *playerCardValue = d.cardNum[playerHand[0].cardNumber];
				//only split 9s if opponent has a 2,3,4,5, or 6
				if (playerCardValue == "2" || playerCardValue == "3" || playerCardValue == "4" || playerCardValue == "5" || playerCardValue == "6") {
					return 2;
				}
			}
			//if opponent doesnt have appropriate card, then hit
			return 0;
		}
		//split 2s, 3s, or 7s only if other player has certain cards
		else if (compCard1Val == "2" || compCard1Val == "3" || compCard1Val == "7") {
			for (int i = 0; i < playerHandSize; i++) {
				char *playerCardValue = d.cardNum[playerHand[0].cardNumber];
				//only split 9s if opponent has a 2,3,4,5,6, or 7
				if (playerCardValue == "2" || playerCardValue == "3" || playerCardValue == "4" || playerCardValue == "5" || playerCardValue == "6" || playerCardValue == "7") {
					return 2;
				}
			}
			return 0;
		}
	}
	//if hand not splittable do
	else {
		int score = handScore(computerHand, d, computerHandSize);
		//these rules onlys apply to hands with 2 cards
		if (computerHandSize == 2) {
			//always hit if hand contains an ace and any card with value 2-6
			if (compCard1Val == "Ace" && (compCard2Val == "2" || compCard2Val == "3" || compCard2Val == "4" || compCard2Val == "5" || compCard2Val == "6")) {
				return 0;
			}
			else if (compCard2Val == "Ace" && (compCard1Val == "2" || compCard1Val == "3" || compCard1Val == "4" || compCard1Val == "5" || compCard1Val == "6")) {
				return 0;
			}
			//always stand if hand contains an ace and an 8 or 9
			else if (compCard1Val == "Ace" && (compCard2Val == "8" || compCard2Val == "9")) {
				return 1;
			}
			else if (compCard2Val == "Ace" && (compCard1Val == "8" || compCard1Val == "9")) {
				return 1;
			}
			//if hand contains and ace and a 7, stand if opponent has a 2-8 card, otherwise hit.
			else if ((compCard1Val == "Ace" && compCard2Val == "7") || (compCard2Val == "Ace" && compCard1Val == "7")) {
				for (int i = 0; i < playerHandSize; i++) {
					char *playerCardValue = d.cardNum[playerHand[0].cardNumber];
					//stand only if opponent has a 2-8 card
					if (playerCardValue == "2" || playerCardValue == "3" || playerCardValue == "4" || playerCardValue == "5" || playerCardValue == "6" || playerCardValue == "7" || playerCardValue == "8") {
						return 1;
					}
				}
				//otherwise hit
				return 0;
			}
		}
		//if the total score is < 11 hit...4 is the minimum score and implies a pair of 2s.  that pair might be split above, it is included
		//here if it is not split
		if (score == 4 || score == 5 || score == 6 || score == 7 || score == 8 || score == 9 || score == 10 || score == 11) {
			return 0;
		}
		//if the score is 17 or above, always stand
		else if (score == 17 || score == 18 || score == 19 || score == 20 || score == 21) {
			return 1;
		}
		//if the score is 13-16, stand if the opponent has a 2-6 card, otherwise hit
		else if (score == 13 || score == 14 || score == 15 || score == 16) {
			for (int i = 0; i < playerHandSize; i++) {
				char *playerCardValue = d.cardNum[playerHand[0].cardNumber];
				//stand only if opponent has a 2-6 card
				if (playerCardValue == "2" || playerCardValue == "3" || playerCardValue == "4" || playerCardValue == "5" || playerCardValue == "6") {
					return 1;
				}
			}
			//otherwise hit
			return 0;
		}
		//if the score = 12, stand if the opponent has a 4-6 card, otherwise hit.
		else if (score == 12) {
			for (int i = 0; i < playerHandSize; i++) {
				char *playerCardValue = d.cardNum[playerHand[0].cardNumber];
				//stand only if opponent has a 2-6 card
				if (playerCardValue == "4" || playerCardValue == "5" || playerCardValue == "6") {
					return 1;
				}
			}
			//otherwise hit
			return 0;
		}
	}
	return 0;
}



int main() {

	seed();
	//used to control when game ends
	bool exit = false;
	int computerChoice = 1;
	//this loop runs until the user exits
	while (!exit) {

		cout << "Would you like the computer to play randomly or with decision tree?" << endl << "Select (1) for random or (2) for decision tree" << endl;
		cin >> computerChoice;

		//A single deck of cards is used for every game
		deck d;
		bool gameOver = false;

		//this bool is used as part of checking if a pair is splittable
		bool initialComputerHand = true;


		//deal initial player hand
		vector<card> hand;
		dealHand(hand, d);
		int handSize = 2;

		vector<card> hand1;
		vector<card> hand2;

		//deal initial computer hand
		vector<card> computerHand;
		dealHand(computerHand, d);
		int compHandSize = 2;

		printHand(hand, d, handSize);
		int score = handScore(hand, d, handSize);

		printComputerHand(computerHand, d, compHandSize);
		int computerScore = handScore(computerHand, d, compHandSize);


		//these are used to track split hands if the player or computer decide to split
		int score1, score2, computerScore1, computerScore2, hand1Size, hand2Size;


		//Initial blackjack for player, computer, or both.  Display message and end game
		if (score == 21 && computerScore != 21) {
			cout << "BLACKJACK!!" << endl;
			gameOver = true;
			cout << "Player wins!!" << endl;
		}
		else if (score != 21 && computerScore == 21) {
			cout << "Computer Blackjack!" << endl;
			gameOver = true;
			cout << "Computer wins!!" << endl;
		}
		else if (score == 21 && computerScore == 21) {
			cout << "Both players have 21.  Result is a push" << endl;
			gameOver = true;
		}

		//if the game isnt over, the player and computer are given turns
		if (!gameOver) {


			//******************************************************************************************************************
			//******************************************************************************************************************
			//******************************************************************************************************************
			//                                               PLAYER TURN
			//******************************************************************************************************************
			//******************************************************************************************************************
			//******************************************************************************************************************


			//INITIAL PLAYER CHOICES
			//player has option to hit, stand, or split if initial hand is a pair
			string playerChoice;
			cout << endl << "       PLAYER TURN" << endl;
			printHand(hand, d, handSize);
			score = handScore(hand, d, handSize);
			cout << "(h)it, (s)tand, or s(p)lit" << endl;
			cin >> playerChoice;
			bool turnOver = false;
			bool playerSplit = false;
			bool computerSplit = false;


			//player hits
			if (playerChoice == "h") {
				turnOver = false;
				hit(hand, d, handSize);
				printHand(hand, d, handSize);
				score = handScore(hand, d, handSize);

				//player busts, end turn
				if (score > 21) {
					cout << "BUST!" << endl;
					turnOver = true;
				}
				//player hits 21, end turn
				else if (score == 21) {
					cout << "Blackjack!" << endl;
					turnOver = true;
				}

				//player has option to keep hitting until busting or deciding to stand
				while (!turnOver) {
					cout << endl << "       PLAYER TURN" << endl;
					printHand(hand, d, handSize);
					score = handScore(hand, d, handSize);
					cout << "(h)it, (s)tand, or s(p)lit" << endl;
					cin >> playerChoice;

					if (playerChoice == "h") {
						hit(hand, d, handSize);
						printHand(hand, d, handSize);
						score = handScore(hand, d, handSize);
						//player busts, end turn
						if (score > 21) {
							cout << "BUST!" << endl;
							turnOver = true;
						}
						//player hits 21, end turn
						else if (score == 21) {
							cout << "Blackjack!" << endl;
							turnOver = true;
						}
					}
					//if player stands, end turn
					else if (playerChoice == "s") {
						cout << "Player stands with a score of " << score << endl;
						turnOver = true;
					}
				}
			}
			//player stands, end turn
			else if (playerChoice == "s") {
				cout << "player stands with a score of " << score << "...but is it enough?" << endl;
				turnOver = true;
			}
			//player splits
			else if (playerChoice == "p") {
				//play both hands

				//check if hand can be split.  cards need to have the same value and be consecutive
				char *card1Val = d.cardNum[hand[0].cardNumber];
				char *card2Val = d.cardNum[hand[1].cardNumber];
				if (card1Val == card2Val) {
					cout << "splitting pair into left and right hands" << endl;
					playerSplit = true;
					//split hand into two hands
					//vector<card> hand1;
					//vector<card> hand2;
					split(hand, hand1, hand2);

					hand1Size = 1;
					hand2Size = 1;

					score1 = 0;
					score2 = 0;

					bool turn1Over = false;
					bool turn2Over = false;

					hit(hand1, d, hand1Size);
					hit(hand2, d, hand2Size);

					printHand(hand1, d, hand1Size);
					score1 = handScore(hand1, d, hand1Size);
					printHand(hand2, d, hand2Size);
					score2 = handScore(hand2, d, hand1Size);

					//21 for either hand
					if (score1 == 21) {
						cout << "BLACKJACK!! with hand 1" << endl;
						turn1Over = true;
					}
					if (score2 == 21) {
						cout << "BLACKJACK!! with hand 2" << endl;
						turn2Over = true;
					}


					//player has option to keep hitting until busting or deciding to stand
					//hand 1 turn
					while (!turn1Over) {
						cout << endl << "       PLAYER TURN" << endl;
						printHand(hand1, d, hand1Size);
						score1 = handScore(hand1, d, hand1Size);
						cout << "hand 1 total is " << score1 << ".  (h)it or (s)tand?" << endl;
						cin >> playerChoice;

						if (playerChoice == "h") {
							hit(hand1, d, hand1Size);
							printHand(hand1, d, hand1Size);
							score1 = handScore(hand1, d, hand1Size);
							if (score1 > 21) {
								cout << "Player busts on hand 1" << endl;
								turn1Over = true;
							}
							else if (score1 == 21) {
								cout << "BLACKJACK!! with hand 1" << endl;
								turn1Over = true;
							}
						}
						else if (playerChoice == "s") {
							cout << "Player stands with a score of " << score1 << " hand 1" << endl;
							turn1Over = true;
						}
					}
					//hand 2 turn
					while (!turn2Over) {
						cout << endl << "       PLAYER TURN" << endl;
						printHand(hand2, d, hand2Size);
						score2 = handScore(hand2, d, hand2Size);
						cout << "hand 2 total is " << score2 << ".  (h)it or (s)tand?" << endl;
						cin >> playerChoice;

						if (playerChoice == "h") {
							hit(hand2, d, hand2Size);
							printHand(hand2, d, hand2Size);
							score2 = handScore(hand2, d, hand2Size);
							if (score2 > 21) {
								cout << "Player busts on hand 2" << endl;
								turn2Over = true;
							}
							else if (score2 == 21) {
								cout << "BLACKJACK!! with hand 2" << endl;
								turn2Over = true;
							}
						}
						else if (playerChoice == "s") {
							cout << "Player stands with a score of " << score2 << " hand 2" << endl;
							turn2Over = true;
						}
					}
				}
				//if cards cannot be split, options are hit or stand
				else {
					cout << "Cannot split cards of different values" << endl;
					cout << "Please choose to (h)it or (s)tay with the current hand" << endl;
					string playerChoice;
					cin >> playerChoice;

					//player hits
					if (playerChoice == "h") {
						turnOver = false;
						hit(hand, d, handSize);
						printHand(hand, d, handSize);
						score = handScore(hand, d, handSize);

						//player busts
						if (score > 21) {
							cout << "Player BUSTS!  Computer wins" << endl;
							turnOver = true;
						}

						//player has option to keep hitting until busting or deciding to stand
						while (!turnOver) {
							cout << endl << "       PLAYER TURN" << endl;
							printHand(hand, d, handSize);
							score = handScore(hand, d, handSize);
							cout << "(h)it or (s)tay" << endl;
							cin >> playerChoice;

							if (playerChoice == "h") {
								hit(hand, d, handSize);
								printHand(hand, d, handSize);
								score = handScore(hand, d, handSize);
								if (score > 21) {
									cout << "Player BUSTS!  Computer wins" << endl;
									turnOver = true;
								}
								else if (score == 21) {
									cout << "Blackjack!" << endl;
									turnOver = true;
								}
							}
							else if (playerChoice == "s") {
								cout << "Player stands with a score of " << score << endl;
								turnOver = true;
							}
						}
					}
					//player stands
					else if (playerChoice == "s") {
						cout << "player stands with a score of " << score << "...but is it enough?" << endl;
						turnOver = true;
					}
				}
			}



			//******************************************************************************************************************
			//******************************************************************************************************************
			//******************************************************************************************************************
			//                                             COMPUTER TURN
			//******************************************************************************************************************
			//******************************************************************************************************************
			//******************************************************************************************************************


			//check if initial hand can be split
			char *compCard1Val = d.cardNum[computerHand[0].cardNumber];
			char *compCard2Val = d.cardNum[computerHand[1].cardNumber];

			printComputerHand(computerHand, d, compHandSize);
			computerScore = handScore(computerHand, d, compHandSize);
			turnOver = false;
			//if initial computer hand is splittable
			if (compCard1Val == compCard2Val) {

				//return random choice of hit, stand, or split
				cout << endl << "      COMPUTER TURN" << endl;
				printComputerHand(computerHand, d, compHandSize);
				computerScore = handScore(computerHand, d, compHandSize);
				cout << "Options are:  hit, stand, split" << endl;

				int decision;
				if (computerChoice == 1) {
					decision = (int)(1.0 * rand() / (RANDMAX + 1) * 3);
					//int decision = 2;
				}
				else if (computerChoice == 2) {
					if (!playerSplit) {
						decision = decide(hand, computerHand, d, handSize, compHandSize, initialComputerHand);
					}
					else {
						for (int i = 0; i < hand2Size; i++) {
							hand1.push_back(hand2[i]);
						}
						decision = decide(hand1, computerHand, d, handSize, compHandSize, initialComputerHand);
					}
				}

				//hit
				if (decision == 0) {
					cout << "computer wants to hit on initial hand" << endl;
					initialComputerHand = false;
					turnOver = false;
					hit(computerHand, d, compHandSize);
					printComputerHand(computerHand, d, compHandSize);
					computerScore = handScore(computerHand, d, compHandSize);

					//Computer busts
					if (computerScore > 21) {
						cout << "Computer BUSTS!" << endl;
						turnOver = true;
					}

					//computer has option to keep hitting until busting or deciding to stand
					while (!turnOver) {
						cout << endl << "      COMPUTER TURN" << endl;
						printComputerHand(computerHand, d, compHandSize);
						computerScore = handScore(computerHand, d, compHandSize);
						cout << "Options are:  hit or stand" << endl;


						if (computerChoice == 1) {
							decision = (int)(1.0 * rand() / (RANDMAX + 1) * 2);
						}
						else if (computerChoice == 2) {
							if (!playerSplit) {
								decision = decide(hand, computerHand, d, handSize, compHandSize, initialComputerHand);
							}
							else {
								for (int i = 0; i < hand2Size; i++) {
									hand1.push_back(hand2[i]);
								}
								decision = decide(hand1, computerHand, d, handSize, compHandSize, initialComputerHand);
							}
						}


						cout << "computer decision:  " << decision << endl;

						if (decision == 0) {
							hit(computerHand, d, compHandSize);
							printComputerHand(computerHand, d, compHandSize);
							computerScore = handScore(computerHand, d, compHandSize);
							if (computerScore > 21) {
								cout << "Computer BUST!" << endl;
								turnOver = true;
							}
							else if (computerScore == 21) {
								cout << "Computer blackjack!" << endl;
								turnOver = true;
							}
						}
						else if (decision == 1) {
							cout << "Computer stands with a score of " << computerScore << endl;
							turnOver = true;
							cout << "computer wants to stand on splitable initial hand" << endl;

						}
					}

				}
				//computer stands
				else if (decision == 1) {
					cout << "computer wants to stand on initial hand" << endl;
					initialComputerHand = false;
				}
				//computer splits
				else if (decision == 2) {
					cout << "computer wants to split initial hand" << endl;

					cout << "splitting pair into left and right hands" << endl;
					computerSplit = true;
					initialComputerHand = false;
					//split hand into two hands
					vector<card> computerHand1;
					vector<card> computerHand2;
					split(computerHand, computerHand1, computerHand2);

					int computerHand1Size = 1;
					int computerHand2Size = 1;
					computerScore1 = 0;
					computerScore2 = 0;
					bool turn1Over = false;
					bool turn2Over = false;


					hit(computerHand1, d, computerHand1Size);
					hit(computerHand2, d, computerHand2Size);

					printComputerHand(computerHand1, d, computerHand1Size);
					computerScore1 = handScore(computerHand1, d, computerHand1Size);


					printComputerHand(computerHand2, d, computerHand2Size);
					computerScore2 = handScore(computerHand2, d, computerHand2Size);

					//21 for either hand
					if (computerScore1 == 21) {
						cout << "Computer BLACKJACK!! with hand 1" << endl;
						turn1Over = true;
					}
					if (computerScore2 == 21) {
						cout << "Computer BLACKJACK!! with hand 2" << endl;
						turn2Over = true;
					}

					//computer has option to keep hitting until busting or deciding to stand
					while (!turn1Over) {
						cout << endl << "      COMPUTER TURN" << endl;
						printComputerHand(computerHand1, d, computerHand1Size);
						computerScore1 = handScore(computerHand1, d, computerHand1Size);
						cout << "Hand 1 options are:  hit or stand" << endl;

						if (computerChoice == 1) {
							decision = (int)(1.0 * rand() / (RANDMAX + 1) * 2);
						}
						else if (computerChoice == 2) {

							if (!playerSplit) {
								decision = decide(hand, computerHand1, d, handSize, computerHand1Size, initialComputerHand);
							}
							else {
								for (int i = 0; i < hand2Size; i++) {
									hand1.push_back(hand2[i]);
								}
								decision = decide(hand1, computerHand1, d, handSize, computerHand1Size, initialComputerHand);
							}
						}

						cout << "computer decision:  " << decision << endl;

						if (decision == 0) {
							cout << "computer wants to hit on hand 1" << endl;
							hit(computerHand1, d, computerHand1Size);
							printComputerHand(computerHand1, d, computerHand1Size);
							computerScore1 = handScore(computerHand1, d, computerHand1Size);
							if (computerScore1 > 21) {
								cout << "Computer BUST!" << endl;
								turn1Over = true;
							}
							else if (computerScore1 == 21) {
								cout << "Computer BLACKJACK!! with hand 1" << endl;
								turn1Over = true;
							}
						}
						else if (decision == 1) {
							cout << "Computer stands with a score of " << computerScore1 << " for hand 1" << endl;
							turn1Over = true;
						}
					}
					while (!turn2Over) {
						cout << endl << "      COMPUTER TURN" << endl;
						printComputerHand(computerHand2, d, computerHand2Size);
						computerScore2 = handScore(computerHand2, d, computerHand2Size);
						cout << "Hand 2 options are:  hit or stand" << endl;


						//Make decision
						if (computerChoice == 1) {
							decision = (int)(1.0 * rand() / (RANDMAX + 1) * 2);
						}
						else if (computerChoice == 2) {
							if (!playerSplit) {
								decision = decide(hand, computerHand2, d, handSize, computerHand2Size, initialComputerHand);
							}
							else {
								for (int i = 0; i < hand2Size; i++) {
									hand1.push_back(hand2[i]);
								}
								decision = decide(hand1, computerHand2, d, handSize, computerHand2Size, initialComputerHand);
							}
						}


						cout << "computer decision:  " << decision << endl;

						if (decision == 0) {
							cout << "computer wants to hit on hand 2" << endl;
							hit(computerHand2, d, computerHand2Size);
							printComputerHand(computerHand2, d, computerHand2Size);
							computerScore2 = handScore(computerHand2, d, computerHand2Size);
							if (computerScore2 > 21) {
								cout << "Computer BUST!" << endl;
								turn2Over = true;
							}
							else if (computerScore2 == 21) {
								cout << "Computer BLACKJACK!! with hand 2" << endl;
								turn2Over = true;
							}
						}
						else if (decision == 1) {
							cout << "Computer stands with a score of " << computerScore2 << " for hand 2" << endl;
							turn2Over = true;
						}
					}

				}

			}
			else {
				//if initial hand cannot be split, return random choice of hit or stand
				cout << endl << "      COMPUTER TURN" << endl;
				printComputerHand(computerHand, d, compHandSize);
				computerScore = handScore(computerHand, d, compHandSize);
				cout << "Hand options are:  hit or stand" << endl;


				//Make decision
				int decision;
				if (computerChoice == 1) {
					decision = (int)(1.0 * rand() / (RANDMAX + 1) * 2);
				}
				else if (computerChoice == 2) {
					if (!playerSplit) {
						decision = decide(hand, computerHand, d, handSize, compHandSize, initialComputerHand);
					}
					else {
						for (int i = 0; i < hand2Size; i++) {
							hand1.push_back(hand2[i]);
						}
						decision = decide(hand1, computerHand, d, handSize, compHandSize, initialComputerHand);
					}
				}


				cout << "computer decision:  " << decision << endl;

				//hit
				if (decision == 0) {
					cout << "computer wants to hit on initial hand" << endl;

					turnOver = false;
					hit(computerHand, d, compHandSize);
					printComputerHand(computerHand, d, compHandSize);
					computerScore = handScore(computerHand, d, compHandSize);

					//Computer busts
					if (computerScore > 21) {
						cout << "Computer BUSTS!" << endl;
						turnOver = true;
					}
					else if (computerScore == 21) {
						cout << "Computer BLACKJACK!!" << endl;
						turnOver = true;
					}

					//player has option to keep hitting until busting or deciding to stand
					while (!turnOver) {

						cout << endl << "      COMPUTER TURN" << endl;
						printComputerHand(computerHand, d, compHandSize);
						computerScore = handScore(computerHand, d, compHandSize);
						cout << "Hand options are:  hit or stand" << endl;

						if (computerChoice == 1) {
							decision = (int)(1.0 * rand() / (RANDMAX + 1) * 2);
						}
						else if (computerChoice == 2) {
							if (!playerSplit) {
								decision = decide(hand, computerHand, d, handSize, compHandSize, initialComputerHand);
							}
							else {
								for (int i = 0; i < hand2Size; i++) {
									hand1.push_back(hand2[i]);
								}
								decision = decide(hand1, computerHand, d, handSize, compHandSize, initialComputerHand);
							}
						}

						//decision = (int)(1.0 * rand() / (RANDMAX + 1) * 2);
						//cin >> playerChoice;

						if (decision == 0) {
							cout << "computer wants to hit after initial hand" << endl;
							hit(computerHand, d, compHandSize);
							printComputerHand(computerHand, d, compHandSize);
							computerScore = handScore(computerHand, d, compHandSize);
							if (computerScore > 21) {
								cout << "Computer BUSTS!" << endl;
								turnOver = true;
							}
							else if (computerScore == 21) {
								cout << "Computer BLACKJACK!!" << endl;
								turnOver = true;
							}
						}
						else if (decision == 1) {
							cout << "Computer stands with a score of " << computerScore << endl;
							turnOver = true;
						}
					}

				}
				//stand
				else if (decision == 1) {
					cout << "computer wants to stand on unsplitable initial hand" << endl;
				}
			}





			//******************************************************************************************************************
			//******************************************************************************************************************
			//******************************************************************************************************************
			//                                            DETERMINE WINNER
			//******************************************************************************************************************
			//******************************************************************************************************************
			//******************************************************************************************************************
			if (!playerSplit && !computerSplit) {
				checkScores(score, computerScore);
			}
			else if (playerSplit && !computerSplit) {
				if (score1 <= 21 && score2 <= 21) {
					if (score1 >= score2) {
						checkScores(score1, computerScore);
					}
					else {
						checkScores(score2, computerScore);
					}
				}
				else if (score1 <= 21 && score2 > 21) {
					checkScores(score1, computerScore);
				}
				else if (score1 > 21 && score2 <= 21) {
					checkScores(score2, computerScore);
				}
				else if (score1 > 21 && score2 > 21) {
					if (computerScore > 21) {
						cout << "Everyone busts.  Result is a push." << endl;
					}
					else {
						cout << "Computer wins" << endl;
					}
				}
			}
			else if (!playerSplit && computerSplit) {
				if (computerScore1 <= 21 && computerScore2 <= 21) {
					if (computerScore1 >= computerScore2) {
						checkScores(score, computerScore1);
					}
					else {
						checkScores(score, computerScore2);
					}
				}
				else if (computerScore1 <= 21 && computerScore2 > 21) {
					checkScores(score, computerScore1);
				}
				else if (computerScore1 > 21 && computerScore2 <= 21) {
					checkScores(score, computerScore2);
				}
				else if (computerScore1 > 21 && computerScore1 > 21) {
					if (score > 21) {
						cout << "Everyone busts.  Result is a push." << endl;
					}
					else {
						cout << "Player wins" << endl;
					}
				}
			}
			else if (playerSplit && computerSplit) {

				int playerScore, compScore;

				if (score1 <= 21 && score1 >= score2) {
					playerScore = score1;
				}
				else if (score2 <= 21 && score1 <= score2) {
					playerScore = score2;
				}
				else if (score1 <= 21 && score2 > 21) {
					playerScore = score1;
				}
				else if (score1 > 21 && score2 <= 21) {
					playerScore = score2;
				}
				//if player busts with both hands
				else if (score1 > 21 && score2 > 21) {
					playerScore = score1;
					//computer wins as long as one hand is <= 21
					if (computerScore1 <= 21 || computerScore2 <= 21) {
						cout << "Computer wins!" << endl;
					}
					else {
						cout << "Everyone busts.  Result is a push" << endl;
					}

				}

				if (computerScore1 <= 21 && computerScore1 >= computerScore2) {
					compScore = computerScore1;
				}
				else if (computerScore2 <= 21 && computerScore1 <= computerScore2) {
					compScore = computerScore2;
				}
				else if (computerScore1 <= 21 && computerScore2 > 21) {
					compScore = computerScore1;
				}
				else if (computerScore1 > 21 && computerScore2 <= 21) {
					compScore = computerScore2;
				}
				else if (computerScore1 > 21 && computerScore2 > 21) {
					compScore = computerScore1;
					//computer wins as long as one hand is <= 21
					if (score1 <= 21 || score2 <= 21) {
						cout << "Player wins!" << endl;
					}
					else {
						cout << "Everyone busts.  Result is a push" << endl;
					}
				}
				checkScores(playerScore, compScore);
			}



		}


		//exit game
		string end;
		cout << "Exit? Y/N" << endl;
		cin >> end;
		if (end == "y") {
			exit = true;
		}
		//d.printDeck();
	}


}