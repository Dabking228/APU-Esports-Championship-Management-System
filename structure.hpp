#pragma once
#include <sstream>
#include <iostream>
#include <functional>
using namespace std;

// Player Structure
class Player {
private:
	int PlayerID = 0;
	string PlayerName;
	int PlayerRating = 0;
	int PlayerPriority = 0;
	bool isCheckedIn = false;


public:
	Player() { }

	Player(int PlayerID, string PlayerName, int PlayerRating, int PlayerPriority) {
		this->isCheckedIn = false;
		this->PlayerID = PlayerID;
		this->PlayerName = PlayerName;
		this->PlayerRating = PlayerRating;
		this->PlayerPriority = PlayerPriority;
	}

	// Normal function goes above here

	//Getter and Setter
	int getPlayerID() { return this->PlayerID; }
	string getPlayerName() { return this->PlayerName; }
	int getPlayerRating() { return this->PlayerRating; }
	int getPlayerPriority() { return this->PlayerPriority; }
	bool getCheckedInStatus() {	return this->isCheckedIn; }
	void toogleCheckIn() { this->isCheckedIn = !this->isCheckedIn; }
};

// Match will need a team, team need 5 player
// once match end, need to have a way to show the game logs and performance
// have public and private team
// PLANNED TO SCRAP TEAM BASED MATCHMAKING

class Team {
private:
	string TeamName;
	int TeamRating = 0;
	const int MAXLENGTH = 5;
	int currentLength = 0;
	Player** PlayerList = new Player*[MAXLENGTH];

	const int MAXTOLERANCE = 4000;
	int TOLERANCE = 0;
	int LOWERBOUND = 0;
	int HIGHERBOUND = 0;
	

	void updateRating() {
		int tempRating = 0;
		for (int i = 0; i < currentLength; i++) {
			tempRating += PlayerList[i]->getPlayerRating();
		}
		this->TeamRating = tempRating / currentLength;
		this->TOLERANCE = (currentLength * MAXTOLERANCE) / (MAXLENGTH - 1);
		this->LOWERBOUND = TeamRating - TOLERANCE;
		this->HIGHERBOUND = TeamRating + TOLERANCE;
	}

public:

	Team() {}
	Team(string TeamName) {
		this->TeamName = TeamName;
	}

	bool addPlayer(Player* player) {
		if (currentLength == MAXLENGTH) { 
			//cout << "Team is Full" << endl; 
			return false; }
		if ((player->getPlayerRating() < LOWERBOUND || player->getPlayerRating() > HIGHERBOUND) && currentLength != 0) {
			//cout << "Player is not within the Bound." << endl;
			return false;
		}

		PlayerList[currentLength] = player;
		currentLength++;

		updateRating();
		return true;
	}

	// This function require the input be starting from 1
	Player* getPlayer(int num){
		if (num <= 0 || num > MAXLENGTH) { return nullptr; }

		return PlayerList[num - 1];
	}

	void getTolerance() {
		cout << "Tolerance: " << TOLERANCE << endl;
		cout << "Lowewr: " << LOWERBOUND << " | Higher: " << HIGHERBOUND << endl;
	}

	void listAllPlayer(function<void (Player*)> func) {
		for (int i = 1; i < currentLength + 1; i++) {
			func(getPlayer(i));
		}
	}

	int getTeamRating() { return this->TeamRating; }
	int getCurrentPlayers() { return this->currentLength; }
	int getMaxPlayers() { return MAXLENGTH; }
	string getTeamName() { return TeamName; }
};



class Match{
private:
	string MatchID;
	string MatchName;
	string Time;

	Player* P1;
	Player* P2;
	
	int scoreP1 = 0;
	int scoreP2 = 0;

	bool isFinish = false;

public:
	Match() {}
	Match(string ID, string name, string time) { this->MatchID = ID; this->MatchName = name; this->Time = time; }




	string getMatchID() { return this->MatchID; }
	string getMatchName() { return this->MatchName; }
	string getTime() { return this->Time; }
};


// viewer can view the stream || need to create a struct for livestream??? || chat???


class Stream {
private:
	string StreamID;
	string StreamName;


public:


};

class Viewer {
private:
	string ViewerID;
	string ViewerName;
	int ViewerPriority;

public:
};

template <typename T> struct Node {
	Node* prev = nullptr;
	T* type;
	Node* next = nullptr;
};