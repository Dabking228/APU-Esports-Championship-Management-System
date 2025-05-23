#pragma once
#include <iostream>
#include "PriorityQueue.hpp"
#include "Stack.hpp"
#include "structure.hpp"
using namespace std;

extern const int MAXTEAM;

class TeamRegister {
private:
	PriorityQueue<Player>* checkInQueue;
	PriorityQueue<Team>* Teams;
	Stack<Player>* WaitingList; // stack for playe that havent check in [check-in = false]
	Stack<Player>* AwaitingList; // This stack is for player when they havent find a team [check-in = true]

	int numOfTeam = 0; // remember to -1
	Team** TeamsRegistered = new Team*[MAXTEAM];


	bool isLoopMenu = true;
	int input = -100;

	void showMenu() {
		cout << "--- Player Check-in and Team Creation ---" << endl;
		cout << "1. Check in Player" << endl;
		cout << "2. List Players" << endl;
		cout << "3. Check Teams and Players" << endl;
		cout << "-1. Exit to Menu" << endl;
	}

	void CheckIn() {
		bool isLoop = true;
		bool isExit = false;
		bool isArrive = false;
		bool isInitTeam = true;

		int choice = -100;

		do {
			if (checkInQueue->isEmpty()) { cout << "The Check in Queue is Empty" << endl; break; }
			// User Interface Loop
			while (isLoop) {
				cout << "--- Check-In Players ---" << endl;
				Player* data = this->checkInQueue->peek();
				cout << "Player Name: " << data->getPlayerName() << endl;
				cout << "Player Rating: " << to_string(data->getPlayerRating()) << endl;
				cout << "1. Arrived" << endl;
				cout << "2. Not Arrived" << endl;
				cout << "-1. Return to Menu" << endl;
				cin >> choice;

				switch (choice) {
				case 1:
					isLoop = false;
					isArrive = true;
					break;
				case 2:
					isLoop = false;
					isArrive = false;
					break;
				case -1:
					isLoop = false;
					isExit = true;
					break;
				default: 
					cout << "Please Select a correct input" << endl;
					break;
				}

				cin.clear();
				cin.ignore(100, '\n');
			}

			// Guard Clause: if the user input -1
			if (isExit) {
				cout << "Exit to Check-In Menu" << endl;
				break;
			}

			Player* data = checkInQueue->deQueue();

			// Guard Clause: if the user enter 1
			if (!isArrive) {
				WaitingList->push(data);
			}

			// Guard Clause: 0 teams? arrived[true]?, create one 
			if (numOfTeam == 0 && isArrive && isInitTeam) {
				stringstream ss;
				ss << "Team " << numOfTeam + 1;

				data->toogleCheckIn();

				Team* team = new Team(ss.str());
				team->addPlayer(data);

				cout << "Joined in " << team->getTeamName() << endl;

				TeamsRegistered[numOfTeam] = team;
				numOfTeam++;
				isInitTeam = false;
			}

			// > 1 teams? arrived[true]?
			if (numOfTeam > 0 && isArrive && isInitTeam) {
				bool joined = false;

				data->toogleCheckIn();

				// Loop Through team and slot the player into the team, if given rating is sufficein 
				for (int i = 0; i < numOfTeam; i++) {
					Team* team = TeamsRegistered[i];
					joined = team->addPlayer(data);

					if(joined){
						cout << "(1) Joined in " << team->getTeamName() << endl;
						break;
					}
				}

				// joined but stack not empty --> loop through the stack
				// failed to join --> back to stack
				if (joined && !AwaitingList->isEmpty()) {
					Player* dataAwait = AwaitingList->pop();
					bool awaitJoined;
					for (int i = 0; i < numOfTeam; i++) {
						Team* team = TeamsRegistered[i];
						awaitJoined = team->addPlayer(dataAwait);
						if (awaitJoined) {
							cout << "Player " << dataAwait->getPlayerName() << " join " << team->getTeamName() << endl;
						}
					}


					if (!awaitJoined) {
						AwaitingList->push(dataAwait);
					}
				}
				// if failed to join  -- not yet reach max team -->  create new team
				else if (!joined && numOfTeam < MAXTEAM) {
					stringstream ss;
					ss << "Team " << numOfTeam + 1;
					Team* newteam = new Team(ss.str());
					newteam->addPlayer(data);

					cout << "(2) Joined in " << newteam->getTeamName() << endl;

					TeamsRegistered[numOfTeam] = newteam;
					numOfTeam++;
					cout << "(2) Created a new team : " << numOfTeam << endl;
				}
				// -- max team created --> put into stack
				else if (!joined && numOfTeam == MAXTEAM) {
					AwaitingList->push(data);
				}
			}

			// reset to next player
			isLoop = true;
			isArrive = false;
			isInitTeam = true;
		} while (!isExit);

		return;
	}

	void checkTeams() {
		if (numOfTeam == 0) { cout << "No Teams" << endl; return; }

		stringstream ss;
		
		bool isLoop = true;
		bool isExit = false;
		int input;

		for (int i = 0; i < numOfTeam; i++) {
			ss << i;
			cout << i+1 << ". " << TeamsRegistered[i]->getTeamRating() << endl;
		}

		while (isLoop) {
			cout << "-1. Exit" << endl;
			cout << "Please enter the team you want to view." << endl;
			cin >> input;

			if (input == -1) {
				isLoop = false;
				break;
			}

			if (input > numOfTeam || input == 0) {
				cout << "Please Select a correct input" << endl;
				cin.clear();
				cin.ignore(100, '\n');
			}

			if (input >= 1 && input <= numOfTeam) {
				cout << "--- Showing Team " << input << " ---" << endl;

				Team* team = TeamsRegistered[input - 1];
				team->listAllPlayer(
					[](Player* p) {
						cout << "Name: " << p->getPlayerName() << endl;
						cout << "Rating: " << p->getPlayerRating() << endl;
						cout << "Status: " << p->getCheckedInStatus() << endl;
					}
				);

				cout << "---" << endl;
				cout << "Press any to return." << endl;
				cin.get();
				cin.clear();
				cin.ignore(1,'\n');
				isLoop = false;
			}
		}

		return;
	}

	void listPlayer() {
		cout << "--- Listing Players ---" << endl;


		cout << "--- Players in Queue ---" << endl;
		checkInQueue->listQueue(
			[](Player* p) { 
				cout << p->getPlayerName() << " | " << p->getPlayerRating() << endl;
			}
		);

		// show all player from awaiting list
		cout << "--- Player in Awaiting List ---" << endl;
		if (!AwaitingList->isEmpty()) {
			Stack<Player> temp = Stack<Player>();
			
			while (!AwaitingList->isEmpty()) {
				Player* p = AwaitingList->pop();
				cout << p->getPlayerName() << " | " << p->getPlayerRating() << endl;
				temp.push(p);
				delete p;
			}
			
			while (!temp.isEmpty()) {
				AwaitingList->push(temp.pop());
			}
		}

		// show all player from waitinglsit
		cout << "-- Player in Waiting List ---" << endl;
		if (!WaitingList->isEmpty()) {
			Stack<Player> temp = Stack<Player>();

			while (!WaitingList->isEmpty()) {
				Player* p = WaitingList->pop();
				cout << p->getPlayerName() << " | " << p->getPlayerRating() << endl;
				temp.push(p);
				delete p;
			}

			while (!temp.isEmpty()) {
				WaitingList->push(temp.pop());
			}
		}

		// show all player from teams
		cout << "--- Player in teams ---" << endl;
		for (int i = 0; i < numOfTeam - 1; i++) {
			Team* team = TeamsRegistered[i];
			team->listAllPlayer(
				[](Player* p) {
					cout << p->getPlayerName() << " | " << p->getPlayerRating() << endl;

				}
			);
		}

		cout << "Press any to return." << endl;
		cin.get();
		cin.clear();
		cin.ignore(1, '\n');
	}

	void queueTeams() {
		for (int i = 0; i < numOfTeam; i++) {
			Team* team = TeamsRegistered[i];

			Teams->enQueue(team, [](Team* t1, Team* t2) { return t1->getTeamRating() > t2->getTeamRating();}, true);
		}
	}

public:
	TeamRegister(PriorityQueue<Player> *Queue, Stack<Player> *WaitingList, Stack<Player> *AwaitingList, PriorityQueue<Team> *Teams) {
		this->checkInQueue = Queue;
		this->WaitingList = WaitingList;
		this->AwaitingList = AwaitingList;
		this->Teams = Teams;
	}

	void openMenu() {
		isLoopMenu = true;
		while (isLoopMenu) {
			showMenu();
			cin >> input;
			switch (input) {
			case 1:
				CheckIn();
				break;
			case 2:
				listPlayer();
				break;
			case 3:
				checkTeams();
				break;
			case -1: 
				isLoopMenu = false; 
				queueTeams();
				break;
			default: {
				cout << "Please Select a correct input" << endl;
				cin.clear();
				cin.ignore(1, '\n');
				break;
				}
			}


		}

	}

};
