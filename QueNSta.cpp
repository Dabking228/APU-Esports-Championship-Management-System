#include <iostream>
#include <fstream>
#include <sstream>
#include "structure.hpp"
#include "Queue.hpp"
#include "PriorityQueue.hpp"
#include "Stack.hpp"
#include "TeamRegister.hpp"
#include "PlayerRegister.hpp"
#include "MatchDashboard.hpp"
#include "LogHistory.hpp"
using namespace std;

string dummyPlayerLoct = "./data/Player.csv";
const int MAXROWplayer = 100;
const int MAXCOLplayer = 5;
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
			// Debug Purpose: print the cell data
			/*if (col == 5) {
				cout << cell << endl;
			}*/
			
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

int main() {
	if (!isPowerOfTwo(MAXTEAM)) { cout << "Team size must be pwr of 2" << endl; return 0; }

	PlayerRegister reg = PlayerRegister(registerPlayer);
	TeamRegister TeamReg = TeamRegister(checkInPlayer, WaitingList, AwaitingList, Teams);
	MatchDashboard MatchDash = MatchDashboard(Teams);
	LogHistory Logs = LogHistory(AwaitingList, MatchDash);
	
	bool isLoopMenu = true;
	int input;

	while (isLoopMenu) {
		cout << endl;
		cout << "--------------------- Main Menu ---------------------" << endl;
		cout << "1. Tournament Registration & Player Queuing" << endl;
		cout << "2. Match Scheduling & Player Progression" << endl;
		cout << "3. Live Stream & Spectator Queue Management" << endl;
		cout << "4. Game Result Logging & Performance History" << endl;
		cout << "-1. Exit System" << endl;
		cin >> input;
		
		switch (input) {
		case 1:
			reg.openMenu();

			init();
			for (int i = 0; i < (sizeof(dummyPlayer) / sizeof(dummyPlayer[0])); i++) {
				dataPlayer[i] = new Player(stoi(dummyPlayer[i][0]), dummyPlayer[i][1], stoi(dummyPlayer[i][2]), stoi(dummyPlayer[i][3]), dummyPlayer[i][4]);
				numPlayer++;
			}

			for (int i = 0; i < numPlayer; i++) {
				registerPlayer->enQueue(dataPlayer[i]);
			}

			while (!registerPlayer->isEmpty()) {
				checkInPlayer->enQueue(registerPlayer->deQueue(), [](Player* p1, Player* p2) {return p1->getPlayerPriority() < p2->getPlayerPriority(); });
			}

			checkInPlayer->listQueue([](Player* p) {
				cout << p->getPlayerName() << " | " << to_string(p->getPlayerRating()) << " | " << to_string(p->getPlayerPriority()) << " | " << p->getPlayerUniversity() << endl;
				});

			TeamReg.openMenu();

			Teams->listQueue([](Team* t) { cout << t->getTeamName() << " | " << t->getTeamRating() << endl; });
			break;

		case 2:
			MatchDash.openMenu();

			if (Teams->getQueueLength() == 1) { cout << "Game Finish Winner: " << Teams->peek()->getTeamName() << endl; }
			break;

		case 3:
			// live stream code
			break;

		case 4:
			Logs.openMenu();
			break;

		case -1:
			isLoopMenu = false;
			cout << "Exiting System..." << endl;
			break;

		default:
			cout << "Please Select a correct input" << endl;
			cin.clear();
			cin.ignore(100, '\n');
			break;
		}
	}

}



