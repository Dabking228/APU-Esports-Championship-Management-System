#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>
#include "structure.hpp"
#include "CircularQueueSpectatorOverflow.hpp"
#include "PriorityQueueSpectator.hpp"

using namespace std;

class Seat {

public:
	// To track the filled seat counts for each section
	int streamerCount = 0;
	int vipCount = 0;
	int normalCount = 0;

	// Create seat structure
	string formatSeat(string id, string name, int width = 20) {
		stringstream ss;
		ss << left << setw(width - 2) << (id + " " + name);
		return "[" + ss.str() + "]";
	}

	string EMPTY_SEAT;

	// Maximum 5 streamers at the front row 
	int streamerMaxSize = 5;
	string streamerSeats[5];

	// Maximum 10 VIPs at the 2nd and 3rd rows
	int vipMaxSize = 10;
	string vipSeats[2][5];

	// Maximum 20 normal spectators from row 4 to 7
	int normalMaxSize = 20;
	string normalSeats[4][5];

	void initSeats() {
		for (int i = 0; i < 5; i++) {
			streamerSeats[i] = EMPTY_SEAT;
			for (int j = 0; j < 2; j++) {
				vipSeats[j][i] = EMPTY_SEAT;
			}
			for (int j = 0; j < 4; j++) {
				normalSeats[j][i] = EMPTY_SEAT;
			}
		}
	}

	// Maximum 20 normal spectators in the overflow queue
	int maxOverflowQueue = 20;
	CircularQueueSpectatorOverflow* overflowQueue;

	// Constructor
	Seat() {
		initSeats();
		overflowQueue = new CircularQueueSpectatorOverflow(maxOverflowQueue);
		EMPTY_SEAT = formatSeat("", "");
	}

	// Destructor
	/*~Seat() {
		delete overflowQueue;
	}*/

	bool isStreamerSeatFull() {
		return streamerCount == streamerMaxSize;
	}

	bool isVipSeatFull() {
		return vipCount == vipMaxSize;
	}

	bool isNormalSeatFull() {
		return normalCount == normalMaxSize;
	}

	void displayAllSeats() {
		cout << "\nStreamer Seats (Row 1):" << endl;
		for (int i = 0; i < streamerMaxSize; i++)
			cout << streamerSeats[i] << " ";
		cout << "\n\nVIP Seats (Row 2 & 3):" << endl;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 5; j++)
				cout << vipSeats[i][j] << " ";
			cout << endl;
		}
		cout << "\nNormal Seats (Row 4 to 7):" << endl;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 5; j++)
				cout << normalSeats[i][j] << " ";
			cout << endl;
		}
	}

	// Clear one seat
	void clearSeat(int row, int col) {
		if (row < 1 || row > 7 || col < 1 || col > 5) {
			cout << "Invalid row or column!" << endl;
			return;
		}
		else if (row == 1) { // For streamer
			// index starts from 0 in array, so col - 1
			if (streamerSeats[col - 1] == EMPTY_SEAT) {
				cout << "The seat is already empty!" << endl;
				return;
			}
			else {
				streamerSeats[col - 1] = EMPTY_SEAT;
				streamerCount--;
			}
		}
		else if (row == 2 || row == 3) { // For VIP
			if (vipSeats[row - 2][col - 1] == EMPTY_SEAT) {
				cout << "The seat is already empty!" << endl;
				return;
			}
			else {
				vipSeats[row - 2][col - 1] = EMPTY_SEAT;
				vipCount--;
			}
		}
		else if (row == 4 || row == 5 || row == 6 || row == 7) { // For Normal 
			if (normalSeats[row - 4][col - 1] == EMPTY_SEAT) {
				cout << "The seat is already empty!" << endl;
				return;
			}
			else {
				normalSeats[row - 4][col - 1] = EMPTY_SEAT;
				normalCount--;
			}
		}
		else { // For non-integer values
			cout << "Invalid input! Please enter an integer value!" << endl;
			return;
		}
		cout << "Seat at Row " << row << " Column " << col << " has been cleared." << endl;
	}

	// Clear all seats
	void clearAllSeats() {
		for (int i = 0; i < 5; i++) {
			streamerSeats[i] = EMPTY_SEAT;
			vipSeats[0][i] = EMPTY_SEAT;
			vipSeats[1][i] = EMPTY_SEAT;
			normalSeats[0][i] = EMPTY_SEAT;
			normalSeats[1][i] = EMPTY_SEAT;
			normalSeats[2][i] = EMPTY_SEAT;
			normalSeats[3][i] = EMPTY_SEAT;
		}
		streamerCount = vipCount = normalCount = 0;
		streamerNextCol = 0;
		vipNextRow = vipNextCol = 0;
		normalNextRow = normalNextCol = 0;
		cout << "All seats are cleared." << endl;
	}

	// Place a spectator into an empty seat
	void replace(int row, int col) {
		if (overflowQueue->isEmpty()) {
			cout << "The circular queue is empty!" << endl;
			return;
		}

		Spectator spectator = overflowQueue->dequeue();

		if (row < 1 || row > 7 || col < 1 || col > 5) {
			cout << "Invalid row or column!" << endl;
			return;
		}
		else if (row == 1) { // For streamer
			// index starts from 0 in array, so col - 1
			if (streamerSeats[col - 1] != EMPTY_SEAT) {
				cout << "The seat is already occupied!" << endl;
				return;
			}
			else {
				if (spectator.getSpectatorPriority() == 1) {
					streamerSeats[col - 1] = formatSeat(spectator.getSpectatorID(), spectator.getSpectatorName());
					streamerCount++;
				}
				else {
					cout << "Spectator is not a streamer and not allowed to be seated here." << endl;
					return;
				}
			}
		}
		else if (row == 2 || row == 3) { // For VIP
			if (vipSeats[row - 2][col - 1] != EMPTY_SEAT) {
				cout << "The seat is already occupied!" << endl;
				return;
			}
			else {
				if (spectator.getSpectatorPriority() == 2) {
					vipSeats[row - 2][col - 1] = formatSeat(spectator.getSpectatorID(), spectator.getSpectatorName());
					vipCount++;
				}
				else {
					cout << "Spectator is not a VIP and not allowed to be seated here." << endl;
					return;
				}
			}
		}
		else if (row == 4 || row == 5 || row == 6 || row == 7) { // For Normal 
			if (normalSeats[row - 4][col - 1] != EMPTY_SEAT) {
				cout << "The seat is already occupied!" << endl;
				return;
			}
			else {
				if (spectator.getSpectatorPriority() == 3) {
					normalSeats[row - 4][col - 1] = formatSeat(spectator.getSpectatorID(), spectator.getSpectatorName());
					normalCount++;
				}
				else {
					cout << "Spectator is not a normal type spectator and not allowed to be seated here." << endl;
					return;
				}
			}
		}
		else { // For non-integer values
			cout << "Invalid input! Please enter an integer value!" << endl;
			return;
		}
		cout << spectator.getSpectatorType() << "-type spectator has been added to Seat at Row " << row << " Column " << col << endl;

	}

	// Clear one seat and put a spectator into the seat
	void clearAndReplace(int row, int col) {
		// If the circular queue is empty, then just clear the seat and no replacement needed.
		if (overflowQueue->isEmpty()) {
			clearSeat(row, col);
			return;
		}

		// If the circular queue is not empty, then clear the seat and replace with a spectator in the circular queue
		clearSeat(row, col);
		replace(row, col);
	}

	// Clear all the seats and replace the overflow normal spectators into the empty seats for normal spectators
	void clearAllAndReplace() {
		// If the circular queue is empty, then just clear the seats and no replacement needed.
		if (overflowQueue->isEmpty()) {
			clearAllSeats();
			return;
		}
		clearAllSeats();
		int row_counter = 4; // Row 4 to 7
		int col_counter = 1; // 5 Columns
		while (!overflowQueue->isEmpty()) {
			replace(row_counter, col_counter);
			col_counter++;
			if (col_counter > 5) {
				col_counter = 1; // Reset to 1
				row_counter++;
			}
			if (row_counter > 7) {
				break;
			}
		}
	}

	/* Assign the seats automatically(for the loading of first 35 spectators in the priority queue)
	   Remember to call clearAllSeats(); to clear all the seats before first loading */

	   // Define pointers for the next available seat position
	int streamerNextCol = 0; // Column 0 - 4 (Single 1D array)
	int vipNextRow = 0, vipNextCol = 0; // 2 Rows (0 - 1), 5 Columns (0 - 4)
	int normalNextRow = 0, normalNextCol = 0; // 4 Rows (0 - 3), 5 Columns (0 - 4)

	bool assignSeatAutomatically(Spectator s) {
		switch (s.getSpectatorPriority()) {
		case 1: // Streamer
			if (streamerNextCol < streamerMaxSize) {
				streamerSeats[streamerNextCol] = formatSeat(s.getSpectatorID(), s.getSpectatorName());
				streamerCount++;
				cout << "Streamer seated at Row 1, Column " << streamerNextCol + 1 << endl;
				streamerNextCol++;
				return true;
			}
			cout << "Streamer seats are full!" << endl;
			break;

		case 2: // VIP
			if (vipNextRow < 2) {
				vipSeats[vipNextRow][vipNextCol] = formatSeat(s.getSpectatorID(), s.getSpectatorName());
				vipCount++;
				cout << "VIP seated at Row " << vipNextRow + 2 << ", Column " << vipNextCol + 1 << endl;
				vipNextCol++;
				if (vipNextCol >= 5) {
					vipNextCol = 0; // Reset to 0
					vipNextRow++;
				}
				return true;
			}
			cout << "VIP seats are full!" << endl;
			break;

		case 3: // Normal Spectator
			if (normalNextRow < 4) {
				normalSeats[normalNextRow][normalNextCol] = formatSeat(s.getSpectatorID(), s.getSpectatorName());
				normalCount++;
				cout << "Normal spectator seated at Row " << normalNextRow + 4 << ", Column " << normalNextCol + 1 << endl;
				normalNextCol++;
				if (normalNextCol >= 5) {
					normalNextCol = 0;
					normalNextRow++;
				}
				return true;
			}
			cout << "Normal spectator seats are full!" << endl;
			break;

		default:
			cout << "Invalid spectator priority!" << endl;
			break;
		}
		return false;
	}
};