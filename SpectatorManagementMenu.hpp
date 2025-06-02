#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <limits>
#include "structure.hpp"
#include "PriorityQueueSpectator.hpp"
#include "CircularQueueSpectatorOverflow.hpp"
#include "SeatManagement.hpp"


using namespace std;

class SpectatorMenu {
	int numberOfSpectators = 0;
	Spectator* SpectatorArray;
	Seat seat;
	PriorityQueueSpectator priorityQueueSpectator;
	CircularQueueSpectatorOverflow circularQueueSpectatorOverflow;

	string SpectatorDataset = "./data/Spectators.csv";
public:
	SpectatorMenu(){}

	int getNumberOfSpectators(string filename) {
		ifstream file(filename);
		if (!file) {
			cerr << "Error in opening Spectators.csv!" << endl;
			return 0;
		}

		string line;
		
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

	void loadSpectatorData() {
		numberOfSpectators = getNumberOfSpectators(SpectatorDataset);
		SpectatorArray = new Spectator[numberOfSpectators];
		loadSpectatorArray(SpectatorDataset, numberOfSpectators, SpectatorArray);
		
	}

	void displayAllSpectators() {
		for (int i = 0; i < numberOfSpectators; i++) {
			Spectator spectator = SpectatorArray[i];
			cout << "[" << spectator.getSpectatorID() << ", " << spectator.getSpectatorName() << ", "
				<< spectator.getSpectatorType() << ", " << spectator.getSpectatorPriority() << "]" << endl;
		}
	}

	void loadPriorityQueue() {
		for (int i = 0; i < numberOfSpectators; i++) {
			priorityQueueSpectator.insertByPriority(SpectatorArray[i], &circularQueueSpectatorOverflow);
		}
		return;
	}


	void openMenu() {
		loadSpectatorData();
		loadPriorityQueue();

		int choice;

		do {
			cout << "--- Spectator Management Dashboard ---" << endl;
			cout << "1. View All Spectators" << endl;
			cout << "2. View Priority Queue" << endl;
			cout << "3. View Overflow Queue" << endl;
			cout << "4. View All Seats" << endl;
			cout << "5. Assign Spectators from Priority Queue" << endl;
			cout << "6. Manually Add Overflow Spectator to Specific Seat" << endl;
			cout << "7. Remove Spectator from Seat" << endl;
			cout << "8. Replace Seat with Overflow Spectator" << endl;
			cout << "9. Clear All Seats" << endl;
			cout << "10. Clear All & Assign Spectators from Overflow" << endl;
			cout << "0. Exit" << endl;
			cout << "Enter your choice: ";
			cin >> choice;

			switch (choice) {
			case 1: displayAllSpectators(); break;

			case 2: priorityQueueSpectator.displaySpectatorPriorityQueue(); break;

			case 3: circularQueueSpectatorOverflow.displayCircularQueue(); break;

			case 4: seat.displayAllSeats(); break;

			case 5: 
				while (!priorityQueueSpectator.isEmpty()) {
					Spectator s = priorityQueueSpectator.deQueue();
					if (!seat.assignSeatAutomatically(s)) {
						// Move to overflow if priority queue is full
						circularQueueSpectatorOverflow.enqueue(s);
					}
				}
				break;

			case 6: 
				int row = 0;
				int col = 0;
				cout << "Enter the row: ";
				cin >> row;
				cout << "\nEnter the column: ";
				cin >> col;
				seat.replace(row, col); break;

			case 7: 
				int row = 0;
				int col = 0;
				cout << "Enter the row: ";
				cin >> row;
				cout << "\nEnter the column: ";
				cin >> col;
				seat.clearSeat(row, col); break;
				
			case 8: 
				int row = 0;
				int col = 0;
				cout << "Enter the row: ";
				cin >> row;
				cout << "\nEnter the column: ";
				cin >> col;
				seat.clearAndReplace(row, col); break;

			case 9: seat.clearAllSeats(); break;

			case 10: seat.clearAllAndReplace(); break;

			case 0: cout << "Exiting..."; break;

			default: cout << "Invalid choice. Try again." << endl;
			}

			cout << endl;
		} while (choice != 0);
	}
};
