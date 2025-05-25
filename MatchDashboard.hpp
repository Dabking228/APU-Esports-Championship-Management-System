#include <iostream>
#include "Stack.hpp"
#include "MatchDetails.hpp"
#include "PriorityQueue.hpp"
#include "structure.hpp"
using namespace std;

extern const int MAXTEAM;

class MatchDashboard {
	bool isLoopMenu;
	int input = -100;

	int numOfMatch = 0;
	PriorityQueue<Team>* Teams;
	Stack<Team>* TourStack= new Stack<Team>();
	Stack<Team>** VsStack;
	MatchDetails** MatchDetail;


	void showMenu() {
		cout << "--- Matchmaking Dashboard ---" << endl;
		cout << "1. Start Matching" << endl;
		cout << "2. Check Ongoing Match Detail" << endl;
		cout << "3. Next Game" << endl;
		cout << "4. Check All Match" << endl;
		cout << "-1. Return to Menu" << endl;
	}

	void checkOngoingMatch() {
		if (numOfMatch == 0) { cout << "Match not started" << endl; return; }

		bool isLoop = true;
		int choice = -100;
		
		// bug here
		cout << "--- Ongoing Match Details ---" << endl;
		for (int i = 0; i < numOfMatch; i++) {
			if (MatchDetail[i]->isMatchFinish()) { continue; }
			cout << i+1 << ". " << MatchDetail[i]->getMatchName() << endl;
		}


		cout << "-1. Return to menu" << endl;
		while (isLoop) {
			cin >> choice;
			if (choice == -1) { isLoop = false; break; }
			if(choice < 1 || choice > numOfMatch){}
			if (MatchDetail[choice - 1]->isMatchFinish()) { cout << "This Match is completed" << endl; isLoop = false; break; }
			MatchDetail[choice - 1]->openMenu();
			return;
		}
	}

	void checkAllMatch() {
		if (numOfMatch == 0) { cout << "Match not started" << endl; return; }

		bool isLoop = true;
		int choice = -100;

		cout << "--- Ongoing Match Details ---" << endl;
		for (int i = 0; i < numOfMatch; i++) {
			cout << i + 1 << ". " << MatchDetail[i]->getMatchName() << endl;
		}


		cout << "-1. Return to menu" << endl;
		while (isLoop) {
			cin >> choice;
			if (choice == -1) { isLoop = false; break; }
			if (choice < 1 || choice > numOfMatch) {}

			MatchDetail[choice - 1]->openMenu();
			return;
		}
	}

	void assignMatch() {
		if (numOfMatch != 0) { cout << "Match started" << endl; return; }
		if (Teams->getQueueLength() == 1) { cout << "Match is either finish/ 1 team only" << endl; return; }

		while (!this->Teams->isEmpty()) {
			Team* temp1 = this->Teams->deQueue();
			Team* temp2 = this->Teams->deQueue(this->Teams->getQueueLength());

		/*	cout << temp1->getTeamName() << endl;
			cout << temp2->getTeamName() << endl;*/

			TourStack->push(temp1);
			TourStack->push(temp2);
		}
		
		numOfMatch = TourStack->getStackLength() / 2;
		VsStack = new Stack<Team>*[numOfMatch];
		MatchDetail = new MatchDetails*[numOfMatch];

		for (int i = 0; i < numOfMatch; i++) {
			VsStack[i] = new Stack<Team>(2);


			VsStack[i]->push(TourStack->pop());
			VsStack[i]->push(TourStack->pop());

			MatchDetail[i] = new MatchDetails();
			MatchDetail[i]->setStack(VsStack[i]);
		}


		cout << "Match is now started" << endl;
	}

	void nextGame() {
		bool allFinish = true;
		for (int i = 0; i < numOfMatch; i++) {
			if (!MatchDetail[i]->isMatchFinish()) {
				allFinish = false;
			}
		}

		if (!allFinish || numOfMatch == 0) { cout << "Matches not yet finish" << endl; return; }
		
		//requeue all winner
		for (int i = 0; i < numOfMatch; i++) {
			Team* winner = MatchDetail[i]->getWinner();
			Teams->enQueue(winner, [](Team* t1, Team* t2) {return t1->getTeamRating() < t2->getTeamRating();});
			delete MatchDetail[i];
		}

		//delete the array and reset numofmatch
		delete[] MatchDetail;
		numOfMatch = 0;

		assignMatch();
	}

public:
	MatchDashboard(PriorityQueue<Team>* teams) {
		this->Teams = teams;
	}

	void openMenu() {
		isLoopMenu = true;
		while (isLoopMenu) {
			showMenu();
			cin >> input;
			switch (input) {
			case 1:
				assignMatch();
				break;
			case 2:
				checkOngoingMatch();
				break;
			case 3:
				nextGame();
				break;
			case 4:
				checkAllMatch();
				break;
			case -1:
				isLoopMenu = false;
				break;
			default:
				cout << "Please Select a correct input" << endl;
				cin.clear();
				cin.ignore(1, '\n');
				break;
			}
		}
			
	}


	MatchDetails** getMatchDetail() {
		return this->MatchDetail;
	}

	int getNumOfMatch() {
		return this->numOfMatch;
	}
};