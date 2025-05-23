#pragma once
#include <iostream>
#include "Queue.hpp"
#include "structure.hpp"
#include "Utils.hpp"
using namespace std;

class PlayerRegister{
private:
	string name;
	int rating = -100;
	int ID = 2000;

	int input = -100;
	Queue<Player>* registerQueue;
	bool isLoopMenu = true;
	
	void showMenu() {
		cout << "--- Player Register ---" << endl;
		cout << "1. Register Player" << endl;
		cout << "2. View Registration" << endl;
		cout << "3. Remove Registration" << endl;
		cout << "-1. Complete and Close Registration" << endl;
	}

	void showQueue() {
		if (registerQueue->isEmpty()) {
			cout << "Queue is Empty." << endl;
			return;
		}

		cout << "ID\t|Name\t|Rating\t" << endl;
		registerQueue->listQueue(
			[](Player* p) {
				return to_string(p->getPlayerID()) + "\t|" + p->getPlayerName() + "\t|" + to_string(p->getPlayerRating());
			}
		);
	}

	void registerPlayer() {
		while (true) {
			cout << "--- Player Register (-1 to exit) ---" << endl;
			cout << "Player Name: ";
			cin >> name;
			if (name == "-1") { break; }
			cout << "Player Rating (1000 ~ 16000): ";
			cin >> rating;
			if (rating == -1) { break; }
			if (rating < 1000 || rating > 16000) { cout << "Rating to high/low. Please Register Again" << endl; break; }
			cout << "Registered" << endl;
			ID++;
			registerQueue->enQueue(new Player(
				ID,
				name,
				rating,
				1
			));
		}
	}

	void removePlayer() {
		bool isLoop = true;
		bool isExit = false;
		int rvChoice = 0;
		string removeBy;
		Player* data = nullptr;

		if (registerQueue->isEmpty()) {
			cout << "Queue is empty." << endl;
			return;
		}

		while (isLoop) {
			cout << "--- Remove Player (-1 to exit) ---" << endl;
			cout << "Choose remove by? \n1. ID \n2. Name" << endl;
			cin >> rvChoice;
			switch (rvChoice) {
			case 1: {
				cout << "Enter ID: ";
				cin >> removeBy;

				data = registerQueue->deQueue(
					registerQueue->getData(removeBy,
						[](Player* p, string removeBy) { return p->getPlayerID() == stoi(removeBy);}
					)
				);
				isLoop = false;
				break;
			}
			case 2: {
				cout << "Enter Name: ";
				cin >> removeBy;

				data = registerQueue->deQueue(
					registerQueue->getData(removeBy,
						[](Player* p, string removeBy) { return tolower(p->getPlayerName()) == tolower(removeBy);}
					)
				);
				isLoop = false;
				break;
			}
			case -1: isLoop = false; isExit = true; break;
			default: {
				cout << "Please Select a correct input" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				break;
				}
			}
		}

		if (data == nullptr && !isExit) {
			cout << "Remove Player Failed" << endl;
			cout << "Returning the Menu" << endl;
			return;
		}
		else if (data != nullptr) {
			cout << "Remove Successfully" << endl;
			ID--;
		}

	}

public:
	PlayerRegister(Queue<Player> *PlayerQueue) {
		bool isFinish;
		this->registerQueue = PlayerQueue;
	}

	void openMenu() {
		isLoopMenu = true;
		while (isLoopMenu) {
			showMenu();
			cin >> input;
			switch (input) {
			case 1: registerPlayer(); break;
			case 2: showQueue(); break;
			case 3: removePlayer(); break;
			case -1: isLoopMenu = false; break;
			default: {
				cout << "Please Select a correct input" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				break;
				}
			}
		}
	}
};