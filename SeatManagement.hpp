#pragma once
#include <iostream>
#include "CircularQueueSpectatorOverflow.hpp"

using namespace std;

class Seat {

public:
	// To track the filled seat counts for each section
	int streamerCount = 0;
	int vipCount = 0;
	int normalCount = 0;

	// Maximum 5 streamers at the front row 
	int streamerMaxSize = 5;
	string streamerSeats[5] = { "[]", "[]", "[]", "[]", "[]" };

	// Maximum 10 VIPs at the 2nd and 3rd rows
	int vipMaxSize = 10;
	string vipSeats[2][5] = {
		{ "[]", "[]", "[]", "[]", "[]" },
		{ "[]", "[]", "[]", "[]", "[]" }
	};

	// Maximum 20 normal spectators from row 4 to 7
	int normalMaxSize = 20;
	string normalSeats[4][5] = {
		{ "[]", "[]", "[]", "[]", "[]" },
		{ "[]", "[]", "[]", "[]", "[]" },
		{ "[]", "[]", "[]", "[]", "[]" },
		{ "[]", "[]", "[]", "[]", "[]" }
	};

	// Maximum 20 normal spectators in the overflow queue
	int maxOverflowQueue = 20;
	CircularQueueSpectatorOverflow*  overflowQueue;

	// Constructor
	Seat() {
		overflowQueue = new CircularQueueSpectatorOverflow(maxOverflowQueue);
	}

	// Destructor
	~Seat() {
		delete overflowQueue;
	}

	bool isStreamerSeatFull() {
		return streamerCount == streamerMaxSize;
	}

	bool isVipSeatFull() {
		return vipCount == vipMaxSize;
	}

	bool isNormalSeatFull() {
		return normalCount == normalMaxSize;
	}

	// Clear one seat
	void clearSeat(int row, int col) {
		if (row < 1 || row > 7 || col < 1 || col > 5) {
			cout << "Invalid row or column" << endl;
		}
		else if (row == 1) { // 

		}
		
	}
};