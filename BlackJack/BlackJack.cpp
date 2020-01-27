// BlackJack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h> 
#include <Windows.h>
#include <limits>
#include <math.h>
using namespace std;
class Card{
	int rank;
	string suit;

	public:
	Card(int new_rank, string new_suit) {
		rank = new_rank;
		suit = new_suit;
	}
	string get_rank() {
		switch (rank) {
		case 11:
			return "Jack";
		case 12:
			return "Queen";
		case 13:
			return "King";
		case 1:
			return "Ace";
		default:
			return to_string(rank);
		}
	}
	int get_number() {
		if (rank < 11) {
			return rank;
		}
		else if (rank > 10) {
			return 10;
		}
	}
	string get_suit() {
		return suit;
	}
	string get_card() {
		return get_rank() + " of " + get_suit();
	}
};

bool continue_play(int &player_money) {
	cout << "Current Money: " << player_money << "\n";
	char response;
	while (true) {
		cout << "Continue? \n" << "y/n \n";
		cin >> response;
		if (response == 'n') {
			cout << "Congratulations! You finished with $" << player_money << "!";
			return false;
		}
		else if (response == 'y') {
			return true;
		}

		else {
			continue;
		}
	}
}

void shuffle(vector<Card>& deck) {
	for (int i = 0; i < 104; i++) {
		Card temp = deck[i % 52];
		int temp_int = rand() % 52;
		deck[i % 52] = deck[temp_int];
		deck[temp_int] = temp;
	}
}

Card next_card(vector<Card> & deck, vector<Card>& backup_deck, int &card_number, bool &new_deck, int &times_run) {
	if (new_deck == false) {
		if (card_number < 52) {
			backup_deck.erase(backup_deck.begin() + card_number - times_run - 1);
			card_number++;
			times_run++;
			return deck[card_number - 2];
		}
		else {
			shuffle(backup_deck);
			card_number = 1;
			new_deck = true;
			return backup_deck[card_number - 1];

		}
	}
	else {
		card_number++;
		return backup_deck[card_number - 1];
	}
	}
bool printcard(string who, int& value, int& alt_value, vector<Card>& deck, vector<Card>& backup_deck, int& card_number, bool& new_deck, int& times_run) {
	Card card = next_card(deck, backup_deck, card_number, new_deck, times_run);
	cout << who << " got a " << card.get_card() << "\n";
	value += card.get_number();
	cout << who << ":";
	if (card.get_rank() == "Ace") {
		alt_value = value + card.get_number() + 10;
		if (alt_value < 21) {
			cout << value << " or " << alt_value;
		}
		else if (alt_value == 21) {
			value = alt_value;
		}
	}
	else {
		alt_value = value;
	}
	cout << value << "\n";
	return true;
}
bool hit(string who, int& value, int& alt_value, vector<Card>& deck, vector<Card>& backup_deck, int& card_number, bool& new_deck, int& times_run) {
	char a;
	while (true) {
		cout << "Hit? " << "y/n \n";
		cin >> a;
		if (a == 'n') {
			return false;
		}
		else if (a == 'y') {
			return printcard(who, value, alt_value, deck, backup_deck, card_number, new_deck, times_run);
		}
		else {
			continue;
		}
	}
}


int main()
{
	/*int a;
		string b;
		cout << "rank? \n";
			cin >> a;
		cout << "suit? \n";
		cin >> b;
		Card c(a, b);
		cout << c.get_rank() << " of " << c.get_suit() << "\n";
		*/
	srand(time(NULL));
	vector<Card> deck = {};
	vector<Card> backup_deck = deck;
	int card_number = 1;
	bool new_deck = false;
	bool continue_playing = true;
	char response;
	int insurance = 50;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 1; j <= 13; j++)
		{
			switch (i)
			{
			case 0:
				deck.push_back(Card(j, "Spades"));
				break;
			case 1:
				deck.push_back(Card(j, "Diamonds"));
				break;
			case 2:
				deck.push_back(Card(j, "Clubs"));
				break;
			case 3:
				deck.push_back(Card(j, "Hearts"));
				break;
			}
		}


	}

	shuffle(deck);

	/*for (int i = 0; i < 52; i++) {
		cout << deck[i].get_card() << endl;
	}

	cout << deck.size();
	*/
	int player_money = 1000;
	cout << "Welcome to Black Jack \n";
	Sleep(500);

	while (continue_playing == true) {
		cout << "You have $" << player_money << "\n";
		int bet;
		int your_value = 0;
		int dealer_value = 0;
		int alt_your_value = 0;
		int alt_dealer_value = 0;
		cout << "What is your bet? \n";
		while (true) {
			cin >> bet;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cout << "Invalid bet. Try again. \n";
				continue;
			}
			if (0 < bet && bet <= player_money) {
				break;
			}
			else {
				cout << "Invalid bet. Try again. \n";
				continue;
			}
		}
		if (new_deck == true) {
			shuffle(deck);
			backup_deck = deck;
			new_deck = false;
		}
		else {
			backup_deck = deck;
		}
		int times_run = 0;
		cout << "Your cards are ";
		Card your_card_1 = next_card(deck, backup_deck, card_number, new_deck, times_run);
		Card your_card_2 = next_card(deck, backup_deck, card_number, new_deck, times_run);
		cout << your_card_1.get_card() << " and " << your_card_2.get_card() << "\n";
		cout << "The dealer has a ";
		Card dealer_card_1 = next_card(deck, backup_deck, card_number, new_deck, times_run);
		Card dealer_card_2 = next_card(deck, backup_deck, card_number, new_deck, times_run);
		cout << dealer_card_1.get_card() << " and a facedown card\n";
		your_value += your_card_1.get_number();
		your_value += your_card_2.get_number();
		alt_your_value = your_value;
		dealer_value += dealer_card_1.get_number() + dealer_card_2.get_number();
		if (your_card_1.get_rank() == "Ace" || your_card_2.get_rank() == "Ace") {
			alt_your_value = your_value + 10;
		}
		cout << "You:" << your_value;
		if (your_value != alt_your_value) {
			cout << " or " << alt_your_value;
		}
		cout << "\n";
		//surrender
		cout << "Would you like to surrender? \n";
		char surr = 'n';
		while (true) {
			cin >> surr;
			if (surr == 'n') {
				cout << "OK \n";
				//insurance
				char insur = 'n';
				if (dealer_card_1.get_rank() == "Ace") {
					cout << "Would you like to make an insurance bet of $50? \n";
					while (true) {
						cin >> insur;
						if (insur == 'n') {
							cout << "OK \n";
							break;
						}
						else if (insur == 'y') {
							player_money -= insurance;
							cout << "OK, you now have $" << player_money;
							Sleep(500);
							break;
						}
						else {
							cout << "Invalid input";
							continue;
						}
					}
				}
				//double down
				cout << "Would you like to double down? \n";
				char doubdown = 'n';
				while (true) {
					cin >> doubdown;
					if (doubdown == 'n') {
						cout << "OK \n";
						while (your_value < 21) {
							if (hit("You", your_value, alt_your_value, deck, backup_deck, card_number, new_deck, times_run) == false) {
								break;
							}
						}
						break;
					}
					else if (doubdown == 'y') {
						bet = min(2 * bet, player_money);
						cout << "Your bet is now $" << bet << "\n";
						Sleep(500);
						printcard("You", your_value, alt_your_value, deck, backup_deck, card_number, new_deck, times_run);
						break;
					}
					else {
						cout << "Invalid input \n";
						continue;
					}
				}
				if (alt_your_value <= 21) {
						your_value = alt_your_value;
				}

				
				if (your_value > 21) {
					cout << "Bust! Your final value is " << your_value << "\n";
					cout << "- $" << bet << "\n";
					player_money -= bet;
				}
				else {
					alt_dealer_value = dealer_value;
					if (dealer_card_1.get_rank() == "Ace" || dealer_card_2.get_rank() == "Ace") {
						alt_dealer_value = dealer_value + 10;
					}
					cout << "Your final value is " << your_value << "\n";
					Sleep(500);
					cout << "Dealer's Turn \n";
					cout << "The facedown card was the " << dealer_card_2.get_card() << "\n";
					cout << "You: " << your_value << " || Dealer: " << dealer_value;
					if (alt_dealer_value != dealer_value) {
						cout << " or " << alt_dealer_value;
					}
					cout << "\n";
					while (dealer_value < 17) {
						Sleep(500);
						if (printcard("The dealer", dealer_value, alt_dealer_value, deck, backup_deck, card_number, new_deck, times_run) == false) {
							break;
						}
					}
					if (alt_dealer_value <= 21) {
						dealer_value = alt_dealer_value;
					}
					if (dealer_value > 21) {
						cout << "Bust! The dealer's final value is " << dealer_value << "\n";
						player_money += bet;
						cout << "You Win! \n";
						cout << "+ $" << bet << "\n";
					}
					else if (dealer_value > your_value) {
						cout << "Dealer Wins \n";
						player_money -= bet;
						cout << "- $" << bet << "\n";
					}
					else if (your_value > dealer_value) {
						cout << "You Win! \n";
						player_money += bet;
						cout << "+ $" << bet << "\n";
					}
					else {
						cout << "You Tied \n";
						cout << "+ $0 \n";
					}
				}
				if (insur == 'y' && dealer_card_2.get_number() == 10) {
					player_money += 2 * insurance;
					cout << "Insurance paid off! \n";
					cout << "+ $" << 2 * insurance << "\n";
				}
				break;
			}
			else if (surr == 'y') {
				"OK, you lose half your bet. \n";
				cout << "- $" << bet / 2 << "\n";
				player_money -= bet / 2;
				break;
			}
			else {
				cout << "Invalid input";
				continue;
			}
		}
			continue_playing = continue_play(player_money);
		}
	}




