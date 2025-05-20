#include <iostream>
#include <fstream>
#include <sstream>
#include "structure.hpp"
#include "Queue.hpp"
#include "PriorityQueue.hpp"
#include "Stack.hpp"
#include "PlayerRegister.hpp"
using namespace std;

string dummyPlayerLoct = "./data/Player.csv";
string dummyPlayer[12][4] = { {} };
int MAXROWplayer = 12;
int MAXCOLplayer = 4;

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


Player** dataPlayer = new Player*[12];
int numPlayer = 0;

// add registere for player, register player will be 1
// add priority queue for register player
// 1 - normal player, 2 - early-bird, 3 - captain
// Player replacement only allow for public team
// private team need to have captain, captain cannot play the game
// Matchmaking based on team rating
// Match flow ?
// update rating ?


int main() {
	Queue<Player> registerPlayer = Queue<Player>("Register Player");
	PriorityQueue<Player> checkInPlayer = PriorityQueue<Player>("Check In");

	PlayerRegister reg = PlayerRegister(registerPlayer);
	reg.openMenu();
	
	init();
	for (int i = 0; i < (sizeof(dummyPlayer) / sizeof(dummyPlayer[0])); i++) {
		dataPlayer[i] = new Player(stoi(dummyPlayer[i][0]),dummyPlayer[i][1],stoi(dummyPlayer[i][2]),stoi(dummyPlayer[i][3]));
		numPlayer++;
	}

	for (int i = 0; i < numPlayer; i++) {
		registerPlayer.enQueue(dataPlayer[i]);
	}
	
	while (!registerPlayer.isEmpty()) {
		checkInPlayer.enQueue(registerPlayer.deQueue(), [](Player* p1, Player* p2) {return p1->getPlayerPriority() < p2->getPlayerPriority();});
	}

	checkInPlayer.listQueue([](Player* p) { return p->getPlayerName() + " | " + to_string(p->getPlayerRating()) + " | " + to_string(p->getPlayerPriority()) ; });

	
	// player register -> close player register [ move register player into check-in ] -> add player from dummy -> [start check-in] 
	// -> player not yet arrive? -> dequeue and requeue -> player arrived? -> dequeue

	// Player withdraw? -> check team -> public? -> slot another player in from queue -> private -> slot another player with Captain info



	//Team T1 = Team("T1");
	//Team T2 = Team("T2");

	//T1.addPlayer(QuePlayer.deQueue());
	//T1.addPlayer(QuePlayer.deQueue());
	//T1.addPlayer(QuePlayer.deQueue());
	//T1.addPlayer(QuePlayer.deQueue());
	//T1.addPlayer(QuePlayer.deQueue());
	//T2.addPlayer(QuePlayer.deQueue());
	//T2.addPlayer(QuePlayer.deQueue());
	//T2.addPlayer(QuePlayer.deQueue());
	//T2.addPlayer(QuePlayer.deQueue());
	//T2.addPlayer(QuePlayer.deQueue());

	//cout << T1.getTeamRating() << endl;
	//cout << T2.getTeamRating() << endl;
	

}

