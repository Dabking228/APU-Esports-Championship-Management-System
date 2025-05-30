#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <limits>
#include "structure.hpp"
#include "Utils.hpp"
#include "Queue.hpp"
#include "PriorityQueue.hpp"
#include "Stack.hpp"
#include "TeamRegister.hpp"
#include "PlayerRegister.hpp"
#include "MatchDashboard.hpp"
using namespace std;

string dummyPlayerLoct = "./data/Player.csv";
const int MAXROWplayer = 100;
const int MAXCOLplayer = 4;
string dummyPlayer[MAXROWplayer][MAXCOLplayer] = { {} };

//Stacks, Queues, Priority Queues, and Circular Queues
void init() {
	ifstream file(dummyPlayerLoct);
	string line;
	int row = 0;

	while (getline(file, line) && row < MAXROWplayer) {
		stringstream ss(line);
		string cell;
		int col = 0;

		while (getline(ss, cell, ',') && col < MAXCOLplayer) {
			dummyPlayer[row][col] = cell;
			col++;
			if (col == 3) {
				cout << cell << endl;
			}
			
		}

		row++;

	}

}


Player** dataPlayer = new Player*[MAXROWplayer];
int numPlayer = 0;


// player max rating will be 16k lowest of 1000
// add registere for player, register player priority will be 1
// add priority queue for register player
// 1 - normal player, 2 - early-bir
// 
// max ptrof2 teams 
// 
// Matchmaking based on team rating


const int MAXTEAM = 8;

Queue<Player>* registerPlayer = new Queue<Player>("Register Player");
PriorityQueue<Player>* checkInPlayer = new PriorityQueue<Player>("Check In");
Stack<Player>* WaitingList = new Stack<Player>("Waiting List");
Stack<Player>* AwaitingList = new Stack<Player>("Awaiting List");
PriorityQueue<Team>* Teams = new PriorityQueue<Team>("Team Registed", MAXTEAM);


// Task 3 Live Stream and Queue Management

string SpectatorDataset = "./data/Spectators.csv";

int getNumberOfSpectators(string filename) {
	ifstream file(filename);
	if (!file) {
		cerr << "Error in opening Spectators.csv!" << endl;
		return 0;
	}

	string line;
	int numberOfSpectators = 0;

	// Skip header
	getline(file, line);

	while (getline(file, line)) {
		stringstream ss(line);
		string spectatorId, spectatorName, spectatorType, spectatorPriorityStr;
		getline(ss, spectatorId, ',');
		getline(ss, spectatorName, ',');
		getline(ss, spectatorType, ',');
		getline(ss, spectatorPriorityStr);

		numberOfSpectators++;
	}
	return numberOfSpectators;
}



void loadSpectatorArray(string filename, int numberOfSpectators, Spectator* SpectatorArray) {
	ifstream file(filename);
	if (!file) {
		cerr << "Error in opening Spectators.csv!" << endl;
		return;
	}

	string line;
	int index = 0;

	// Skip header
	getline(file, line);

	while (getline(file, line) && index < numberOfSpectators) {
		stringstream ss(line);
		string spectatorId, spectatorName, spectatorType, spectatorPriorityStr;
		getline(ss, spectatorId, ',');
		getline(ss, spectatorName, ',');
		getline(ss, spectatorType, ',');
		getline(ss, spectatorPriorityStr);

		SpectatorArray[index] = Spectator(spectatorId, spectatorName, spectatorType, spectatorPriorityStr);
		index++;
	}
	cout << "Successfully loaded all spectators" << endl;
	
}

int main() {
	chrono::time_point<chrono::system_clock> start, end;
	start = chrono::system_clock::now();
	SIZE_T spectatorMemoryBefore = getCurrentMemoryUsage();
	int numberOfSpectators = getNumberOfSpectators(SpectatorDataset);
	Spectator* SpectatorArray = new Spectator[numberOfSpectators];
	loadSpectatorArray(SpectatorDataset, numberOfSpectators, SpectatorArray);
	for (int i = 0; i < numberOfSpectators; i++) {
		Spectator spectator = SpectatorArray[i];
		cout << "[" << spectator.getSpectatorID() << ", " << spectator.getSpectatorName() << ", "  
			<< spectator.getSpectatorType() << ", " << spectator.getSpectatorPriority() << "]" << endl;
	}
	end = chrono::system_clock::now();
	chrono::duration<double> taken = end - start;
	cout << "\nTime taken: " << taken.count() << " seconds" << endl;
	SIZE_T spectatorMemoryAfter = getCurrentMemoryUsage();
	cout << "Memory used: " << (spectatorMemoryAfter - spectatorMemoryBefore) / 1024 << " KB" << endl;
	return 0;

}
	/*
	if (!isPowerOfTwo(MAXTEAM)) { cout << "Team size must be pwr of 2" << endl; return 0; }

	PlayerRegister reg = PlayerRegister(registerPlayer);
	TeamRegister TeamReg = TeamRegister(checkInPlayer, WaitingList, AwaitingList, Teams);
	MatchDashboard MatchDash = MatchDashboard(Teams);

	reg.openMenu();

	init();
	for (int i = 0; i < (sizeof(dummyPlayer) / sizeof(dummyPlayer[0])); i++) {
		dataPlayer[i] = new Player(stoi(dummyPlayer[i][0]),dummyPlayer[i][1],stoi(dummyPlayer[i][2]),stoi(dummyPlayer[i][3]));
		numPlayer++;
	}

	for (int i = 0; i < numPlayer; i++) {
		registerPlayer->enQueue(dataPlayer[i]);
	}

	while (!registerPlayer->isEmpty()) {
		checkInPlayer->enQueue(registerPlayer->deQueue(), [](Player* p1, Player* p2) {return p1->getPlayerPriority() < p2->getPlayerPriority();});
	}

	checkInPlayer->listQueue([](Player* p) { return p->getPlayerName() + " | " + to_string(p->getPlayerRating()) + " | " + to_string(p->getPlayerPriority()) ; });

	TeamReg.openMenu();

	Teams->listQueue([](Team* t) { cout << t->getTeamName() << " | " << t->getTeamRating() << endl;});

	MatchDash.openMenu();

	if (Teams->getQueueLength() == 1) { cout << "Game Finish Winner: " << Teams->peek()->getTeamName() << endl; }

	*/


