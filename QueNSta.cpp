#include <iostream>

#include "Queue.hpp"

using namespace std;

//Stacks, Queues, Priority Queues, and Circular Queues

// {PlayerID, PlayerName, PlayerRating}
string PLAYER_SAMPLE_LIST[][3] = {
	{"10001", "Test 1", "10000"},
	{"10002", "Test 2", "10200"}
};






int main() {
	Queue<int> temp = Queue<int>("Hello world");

	temp.enQueue(20);
	temp.enQueue(40);
	temp.enQueue(60);
	temp.enQueue(100);
	temp.enQueue(120);


	temp.listQueue();

	cout << endl;
	cout << temp.deQueue() << endl;
	temp.listQueue();

	cout << endl;
	cout << temp.deQueue(60) << endl;
	temp.listQueue();

	cout << temp.getQueueLength() << endl;
	

	return 0;
}