#pragma once
#include <sstream>
#include <iostream>
using namespace std;

// Player Structure
class Player {
private:
	int PlayerID;
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
};

// Match will need a team, team need 5 player
// once match end, need to have a way to show the game logs and performance
// have public and private team
class Team {
	string TeamName;

private:
	const int MAXLENGTH = 5;
	int currentLength = 0;
	Player** PlayerList = new Player*[MAXLENGTH];
	int TeamRating = 0;

	Player* Captain = nullptr;
	bool isPrivate = false;

	void updateRating() {
		int tempRating = 0;
		for (int i = 0; i < currentLength; i++) {
			tempRating += PlayerList[i]->getPlayerRating();
		}
		this->TeamRating = tempRating / currentLength;
	}

public:
	Team() {}
	Team(string TeamName) {
		this->TeamName = TeamName;
	}

	Team(string TeamName, Player* Captain) {
		this->TeamName = TeamName;
		this->Captain = Captain;
		this->isPrivate = true;
	}


	void addPlayer(Player* player) {
		if (currentLength == MAXLENGTH) { cout << "Team is Full" << endl; return; }
		if (isPrivate) { cout << "Team is private, Please include Captain in Params" << endl; return; }

		PlayerList[currentLength] = player;
		currentLength++;

		updateRating();
	}

	void addPlayer(Player* player, Player* Captain) {
		if (currentLength == MAXLENGTH) { cout << "Team is Full" << endl; return; }
		if (isPrivate && player == Captain) { cout << "Captain cannot be added into Player" << endl; return; }
		
		PlayerList[currentLength] = player;
		currentLength++;

		updateRating();
	}

	int getTeamRating() { return this->TeamRating; }
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