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
	string PlayerUniversity;
	bool isCheckedIn = false;


public:
	Player() { }

	Player(int PlayerID, string PlayerName, int PlayerRating, int PlayerPriority, string PlayerUniversity) {
		this->isCheckedIn = false;
		this->PlayerID = PlayerID;
		this->PlayerName = PlayerName;
		this->PlayerRating = PlayerRating;
		this->PlayerPriority = PlayerPriority;
		this->PlayerUniversity = PlayerUniversity;
	}

	// Normal function goes above here

	//Getter and Setter
	int getPlayerID() { return this->PlayerID; }
	string getPlayerName() { return this->PlayerName; }
	int getPlayerRating() { return this->PlayerRating; }
	int getPlayerPriority() { return this->PlayerPriority; }
	string getPlayerUniversity() { return this->PlayerUniversity; }

	bool getCheckedInStatus() {	return this->isCheckedIn; }
	void toogleCheckIn() { this->isCheckedIn = !this->isCheckedIn; }

	void setPlayerRating(int rating) { this->PlayerRating = rating; }
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
	~Team() {
		for (int i = 0; i < currentLength; i++) {
			delete PlayerList[i];
		}
		delete[] PlayerList;
	}
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
		cout << "debug: " << this->getTeamName()<< endl;
		for (int i = 1; i < currentLength + 1; i++) {

			func(getPlayer(i));
		}
	}


	bool isTeamFull() { if (currentLength == MAXLENGTH) { return true; } return false; }
	int getTeamRating() { return this->TeamRating; }
	int getCurrentPlayers() { return this->currentLength; }
	int getMaxPlayers() { return MAXLENGTH; }
	string getTeamName() { return TeamName; }
};

// viewer can view the stream || need to create a struct for livestream??? || chat???


class Spectator {
private:
	string SpectatorID;
	string SpectatorName;
	string SpectatorType;
	int SpectatorPriority;

public:
	Spectator() {
		SpectatorID = "";
		SpectatorName = "";
		SpectatorType = "";
		SpectatorPriority = 0;
	}

	Spectator(string SpectatorID, string SpectatorName, string SpectatorType, string SpectatorPriorityText) {
		this->SpectatorID = SpectatorID;
		this->SpectatorName = SpectatorName;
		this->SpectatorType = SpectatorType;
		try {
			SpectatorPriority = stoi(SpectatorPriorityText);
		}
		catch (...) {
			throw invalid_argument("Spectator Priority Error");
		}
	}

	string getSpectatorID() { return SpectatorID; }
	string getSpectatorName() { return SpectatorName; }
	string getSpectatorType() { return SpectatorType; }
	int getSpectatorPriority() { return SpectatorPriority; }
};

template <typename T> struct Node {
	Node* prev = nullptr;
	T* type;
	Node* next = nullptr;
};

class MatchResult {
private:
	string matchName;
	string team1;
	string team2;
	int score1;
	int score2;
	string winner;
	string playerList;
	string highlight;

public:
	MatchResult() {

	}

	MatchResult(string matchName, string team1, int score1, string team2, int score2, string winner, string playerList, string highlight) {
		this->matchName = matchName;
		this->team1 = team1;
		this->team2 = team2;
		this->score1 = score1;
		this->score2 = score2;
		this->winner = winner;
		this->playerList = playerList;
		this->highlight = highlight;
	}

	string getMatchName() const { return matchName; }
	string getTeam1() const { return team1; }
	string getTeam2() const { return team2; }
	int getScore1() const { return score1; }
	int getScore2() const { return score2; }
	string getWinner() const { return winner; }
	string getPlayerList() const { return playerList; }
	string getHighlight() const { return highlight; }

	void setMatchName(string name) {
		this->matchName = matchName;
	}

};

struct RankedPlayer {
	Player* player;
	string result;
};

class TournamentDetails {
private:
	string date;
	string venue;
	string name;
	string avgDuration;
	string winner;
	int teamRating;
	int totalViewers;
	string player1;
	string uni1;
	string player2;
	string uni2;
	string player3;
	string uni3;
	string player4;
	string uni4;
	string player5;
	string uni5;

public:
	TournamentDetails(string date, string venue, string name, string avgDuration,
		string winner, int teamRating, int totalViewers,
		string player1, string uni1,
		string player2, string uni2,
		string player3, string uni3,
		string player4, string uni4,
		string player5, string uni5) {
		this->date = date;
		this->venue = venue;
		this->name = name;
		this->avgDuration = avgDuration;
		this->winner = winner;
		this->teamRating = teamRating;
		this->totalViewers = totalViewers;
		this->player1 = player1;
		this->uni1 = uni1;
		this->player2 = player2;
		this->uni2 = uni2;
		this->player3 = player3;
		this->uni3 = uni3;
		this->player4 = player4;
		this->uni4 = uni4;
		this->player5 = player5;
		this->uni5 = uni5;
	}

	string getDate() { return date; }
	string getVenue() { return venue; }
	string getName() { return name; }
	string getAvgDuration() { return avgDuration; }
	string getWinner() { return winner; }
	int getTeamRating() { return teamRating; }
	int getTotalViewers() { return totalViewers; }
	string getPlayer1() { return player1; }
	string getUni1() { return uni1; }
	string getPlayer2() { return player2; }
	string getUni2() { return uni2; }
	string getPlayer3() { return player3; }
	string getUni3() { return uni3; }
	string getPlayer4() { return player4; }
	string getUni4() { return uni4; }
	string getPlayer5() { return player5; }
	string getUni5() { return uni5; }
};