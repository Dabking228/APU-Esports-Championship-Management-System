#include <iostream>
#include "structure.hpp"
#include "Queue.hpp"
#include "PriorityQueue.hpp"

using namespace std;

//Stacks, Queues, Priority Queues, and Circular Queues

// {PlayerID, PlayerName, PlayerRating, Priority}
string PLAYER_SAMPLE_LIST[][4] = {
	{"10001", "Test 1", "10000", "3"},
	{"10002", "Test 2", "10200", "2"},
	{"10003", "Test 3", "12033", "1"},
	{"10004", "Test 4", "12321", "1"},
	{"10005", "Test 5", "25433", "3"},
	{"10006", "Test 6", "54312", "2"},
	{"10007", "Test 7", "55643", "2"},
};



int main() {
	//Queue<Player> temp = Queue<Player>("NAME GOES HERE");


	//for (int i = 0; i < (sizeof(PLAYER_SAMPLE_LIST) / sizeof(PLAYER_SAMPLE_LIST[0])); i++) {
	//	temp.enQueue(
	//		Player(PLAYER_SAMPLE_LIST[i][0], PLAYER_SAMPLE_LIST[i][1], stoi(PLAYER_SAMPLE_LIST[i][2]), stoi(PLAYER_SAMPLE_LIST[i][3]))
	//	);
	//}

	//temp.listQueue([](Player p) -> string {return p.getPlayerName(); });
	//cout << temp.front().getPlayerName() << endl;

	PriorityQueue<Player> Ptemp = PriorityQueue<Player>("P NAme goes here");
	for (int i = 0; i < (sizeof(PLAYER_SAMPLE_LIST) / sizeof(PLAYER_SAMPLE_LIST[0])); i++) {
		Ptemp.enQueue(
			Player(PLAYER_SAMPLE_LIST[i][0], PLAYER_SAMPLE_LIST[i][1], stoi(PLAYER_SAMPLE_LIST[i][2]), stoi(PLAYER_SAMPLE_LIST[i][3])),
			[](Player p1, Player p2) -> bool {return p1.getPlayerPriority() < p2.getPlayerPriority();}
		);
		Ptemp.listQueue([](Player p) -> string {return p.getPlayerName() + " | " + to_string(p.getPlayerPriority()); });
		cout << endl;
	}

}


//int main() {
//	Queue<int> temp = Queue<int>("Hello world");
//
//	temp.enQueue(20);
//	temp.enQueue(40);
//	temp.enQueue(60);
//	temp.enQueue(100);
//	temp.enQueue(120);
//
//
//	temp.listQueue();
//
//	cout << endl;
//	cout << temp.deQueue() << endl;
//	temp.listQueue();
//
//	cout << endl;
//	cout << temp.deQueue(60) << endl;
//	temp.listQueue();
//
//	cout << temp.getQueueLength() << endl;
//	
//
//	return 0;
//}