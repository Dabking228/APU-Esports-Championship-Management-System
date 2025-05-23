#include <iostream>
#include <fstream>
#include <sstream>
#include "structure.hpp"
#include "Queue.hpp"
#include "PriorityQueue.hpp"
#include "Stack.hpp"
#include "TeamRegister.hpp"
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


// player max rating will be 16k lowest of 1000
// add registere for player, register player priority will be 1
// add priority queue for register player
// 1 - normal player, 2 - early-bird, 3 - VIP
// handle check-ins
// max 8 teams (40 players)
// max private team 4 teams
// Player replacement only allow for public team
// Matchmaking based on team rating
// Match flow ?
// update rating ?

const int MAXTEAM = 8;

Queue<Player>* registerPlayer = new Queue<Player>("Register Player");
PriorityQueue<Player>* checkInPlayer = new PriorityQueue<Player>("Check In");
Stack<Player>* WaitingList = new Stack<Player>("Waiting List");
Stack<Player>* AwaitingList = new Stack<Player>("Awaiting List");
PriorityQueue<Team>* Teams = new PriorityQueue<Team>("Team Registed", MAXTEAM);

int main() {

	PlayerRegister reg = PlayerRegister(registerPlayer);
	TeamRegister TeamReg = TeamRegister(checkInPlayer, WaitingList, AwaitingList, Teams);
	
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

