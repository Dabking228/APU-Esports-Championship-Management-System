#include <iostream>
#include <sstream>
#pragma once
using namespace std;

class MatchDetails {
	bool isLoopMenu;
	int input = -100;

	int T1P = 0;
	int T2P = 0;

	string MatchName;
	Stack<Team>* VS;
	Team* Winner;
	Team* Loser;
	bool matchFinish = false;

	void showMenu() {
		cout << "--- Match " << this->MatchName << " ---" << endl;
		cout << getT1Data()->getTeamName() << " " << T1P << " | " << T2P << " " << getT2Data()->getTeamName() << endl;
		cout << "1. Check Teams" << endl;
		cout << "2. +1 to " << getT1Data()->getTeamName() << endl;
		cout << "3. +1 to " << getT2Data()->getTeamName() <<endl;
		cout << "-1. Back to Menu" << endl;
	}

	void checkTeam() {
		Team* t1 = VS->pop();
		Team* t2 = VS->peek();

		cout << "--- " << t1->getTeamName() << " ---" << endl;
		t1->listAllPlayer([](Player* p) {
			cout << p->getPlayerName() << " | " << p->getPlayerRating() << endl;
		});
		VS->push(t1);


		cout << "--- " << t2->getTeamName() << " ---" << endl;
		t2->listAllPlayer([](Player* p) {
			cout << p->getPlayerName() << " | " << p->getPlayerRating() << endl;
		});

		cin.get();
		cin.clear();
		cin.ignore(1, '\n');
	}

	void addPoint(int index) {
		if (T1P == 3 || T2P == 3) { cout << "Match Finished" << endl; return; }

		if (index == 1) {
			T1P++;
		}

		if (index == 2) {
			T2P++;
		}

		if (T1P == 3 || T2P == 3) {
			cout << "Match Finished" << endl;
			matchFinish = true;
			return;
		}
	}

	void whoWinner() {
		if (!matchFinish) { return; }
		if (T1P > T2P) {
			Winner = VS->peek();
			Team* t1 = VS->pop();
			Loser = VS->peek();
			VS->push(t1);
		}
		else {
			Loser = VS->peek();
			Team* t1 = VS->pop();
			Winner = VS->peek();
			VS->push(t1);
		}
	}

public:
	
	~MatchDetails() {

	}

	MatchDetails(){}


	Team* getT1Data() {
		Team* t = VS->peek();
		return t;
	}

	Team* getT2Data() {
		Team* t1 = VS->pop();
		Team* t2 = VS->peek();
		VS->push(t1);

		return t2;
	}

	void setStack(Stack<Team>* t) {
		this->VS = t;
		stringstream ss;

		Team* team = t->pop();
		ss << team->getTeamName() << " VS " << VS->peek()->getTeamName();
		VS->push(team);

		this->MatchName = ss.str();
	}

	void openMenu() {
		isLoopMenu = true;
		while (isLoopMenu) {
			showMenu();
			cin >> input;
			switch (input) {
			case 1:
				checkTeam();
				break;
			case 2: 
				addPoint(1);
				break;
			case 3: 
				addPoint(2);
				break;
			case -1:
				isLoopMenu = false; 
				whoWinner();
				cout << "Back to dashboard" << endl;
				break;
			default: 
				cout << "Please Select a correct input" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				break;
			}
		}
	}

	Team* getWinner() { 
		if (matchFinish) {
			return Winner;
		}

		return nullptr;
	}

	Team* getLoser() {
		if (matchFinish) {
			return Loser;
		}

		return nullptr;
	}

	int getT1Score() {
		return T1P;
	}

	int getT2Score() {
		return T2P;
	}

	bool isMatchFinish() { return this->matchFinish; }
	string getMatchName() { return this->MatchName; }
};