#pragma once
#include <sstream>
#include <iostream>
using namespace std;

// Player Structure
class Player {
private:
	string PlayerID;
	string PlayerName;
	int PlayerRating;
	bool isCheckedIn;


public:
	Player() { }

	Player(string PlayerID, string PlayerName, int PlayerRating) {
		this->isCheckedIn = false;
		this->PlayerID = PlayerID;
		this->PlayerName = PlayerName;
		this->PlayerRating = PlayerRating;
	}




	// Normal function goes above here

	/* 
	Getter and Setter
	*/
	string getPlayerID() {
		return this->PlayerID;
	}
	string getPlayerName() {
		return this->PlayerName;
	}
	int getPlayerRating() {
		return this->PlayerRating;
	}
	bool getCheckedInStatus() {
		return this->isCheckedIn;
	}
};

// Match will need a team, team need 5 player
// once match end, need to have a way to show the game logs and performance
class Team {
	string TeamName;

private:
	const int MAXLENGTH = 5;
	int currentLength = 0;
	Player* PlayerList = new Player[5];
	int TeamRating;

	void updateRating() {
		int tempRating = 0;
		for (int i = 0; i < currentLength; i++) {
			tempRating += PlayerList[i].getPlayerRating();
		}
		this->TeamRating = tempRating / currentLength;
	}

public:
	Team() {}
	Team(string TeamName) {
		this->TeamName = TeamName;
		this->TeamRating = 0;
	}

	void setPlayer(Player player) {
		if (currentLength == MAXLENGTH) {
			cout << "Team is full" << endl;
			return;
		}
		PlayerList[currentLength] = player;
		updateRating();
		currentLength++;
	}
};



class Match{
private:
	string MatchID;
	string MatchName;
	string Time;

	Team* Team1;
	Team* Team2;

	bool isFinish;

public:
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