#include <iostream>
#include <fstream>
#include <sstream>
#include "structure.hpp"
#include "Queue.hpp"
#include "PriorityQueue.hpp"
#include "Stack.hpp"
#include "TeamRegister.hpp"
#include "PlayerRegister.hpp"
#include "MatchDashboard.hpp"
#include "LogHistory.hpp"
#include "PriorityQueueSpectator.hpp"
#include "CircularQueueSpectatorOverflow.hpp"
#include "SeatManagement.hpp"
#include "SpectatorManagementMenu.hpp"

using namespace std;

string dummyPlayerLoct = "./data/Player.csv";
const int MAXROWplayer = 100;
const int MAXCOLplayer = 5;
string dummyPlayer[MAXROWplayer][MAXCOLplayer] = { {} };

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
			// Debug Purpose: print the cell data
			/*if (col == 5) {
				cout << cell << endl;
			}*/
			
		}

		row++;

	}

}

PriorityQueue<TournamentDetails> loadTournamentsToQueue(const string& filename) {
	PriorityQueue<TournamentDetails> tournamentQueue;
	ifstream file(filename);
	string line;

	//higher viewcount = higher priority
	auto comparator = [](TournamentDetails* a, TournamentDetails* b) {
		return a->getTotalViewers() > b->getTotalViewers();
	};

	while (getline(file, line)) {
		stringstream ss(line);
		string date, venue, name, avgDuration, winner, teamRatingStr, totalViewersStr;
		string p1, u1, p2, u2, p3, u3, p4, u4, p5, u5;

		getline(ss, date, ',');
		getline(ss, venue, ',');
		getline(ss, name, ',');
		getline(ss, avgDuration, ',');
		getline(ss, winner, ',');
		getline(ss, teamRatingStr, ',');
		getline(ss, totalViewersStr, ',');
		getline(ss, p1, ','); getline(ss, u1, ',');
		getline(ss, p2, ','); getline(ss, u2, ',');
		getline(ss, p3, ','); getline(ss, u3, ',');
		getline(ss, p4, ','); getline(ss, u4, ',');
		getline(ss, p5, ','); getline(ss, u5);

		int teamRating = stoi(teamRatingStr);
		int totalViewers = stoi(totalViewersStr);

		TournamentDetails* t = new TournamentDetails(date, venue, name, avgDuration, winner, teamRating, totalViewers,
			p1, u1, p2, u2, p3, u3, p4, u4, p5, u5);

		tournamentQueue.enQueue(t, comparator);
	}

	return tournamentQueue;
}


void addTournamentDetails(PriorityQueue<Team>* Teams, PriorityQueue<TournamentDetails> PastTournaments) {
	string winner = Teams->peek()->getTeamName();
	int rating = Teams->peek()->getTeamRating();
	string player1 = Teams->peek()->getPlayer(1)->getPlayerName();
	string uni1 = Teams->peek()->getPlayer(1)->getPlayerUniversity();
	string player2 = Teams->peek()->getPlayer(2)->getPlayerName();
	string uni2 = Teams->peek()->getPlayer(2)->getPlayerUniversity();
	string player3 = Teams->peek()->getPlayer(3)->getPlayerName();
	string uni3 = Teams->peek()->getPlayer(3)->getPlayerUniversity();
	string player4 = Teams->peek()->getPlayer(4)->getPlayerName();
	string uni4 = Teams->peek()->getPlayer(4)->getPlayerUniversity();
	string player5 = Teams->peek()->getPlayer(5)->getPlayerName();
	string uni5 = Teams->peek()->getPlayer(5)->getPlayerUniversity();

	TournamentDetails* td = new TournamentDetails("14/06/2025", "Virtual", "APU All Stars Tournament", "0:40:54", winner, rating, 450, player1, uni1, player2, uni2, player3, uni3, player4, uni4, player5, uni5);
	
	//higher viewcount = higher priority
	auto comparator = [](TournamentDetails* a, TournamentDetails* b) {
		return a->getTotalViewers() > b->getTotalViewers();
	};

	PastTournaments.enQueue(td, comparator);
}


Player** dataPlayer = new Player*[MAXROWplayer];
int numPlayer = 0;


// player max rating will be 16k lowest of 1000
// add registere for player, register player priority will be 1
// add priority queue for register player
// 1 - normal player, 2 - early-bir
// 
// max ptrof2 teams 
// 
// Matchmaking based on team rating


const int MAXTEAM = 8;

Queue<Player>* registerPlayer = new Queue<Player>("Register Player");
PriorityQueue<Player>* checkInPlayer = new PriorityQueue<Player>("Check In");
Stack<Player>* WaitingList = new Stack<Player>("Waiting List");
Stack<Player>* AwaitingList = new Stack<Player>("Awaiting List");
PriorityQueue<Team>* Teams = new PriorityQueue<Team>("Team Registed", MAXTEAM);
PriorityQueue<TournamentDetails> PastTournaments = loadTournamentsToQueue("./data/PastTournament.csv");

int main() {
	if (!isPowerOfTwo(MAXTEAM)) { cout << "Team size must be pwr of 2" << endl; return 0; }

	PlayerRegister reg = PlayerRegister(registerPlayer);
	TeamRegister TeamReg = TeamRegister(checkInPlayer, WaitingList, AwaitingList, Teams);
	MatchDashboard MatchDash = MatchDashboard(Teams);
	LogHistory Logs = LogHistory(MatchDash, PastTournaments);
	SpectatorMenu specDashboard = SpectatorMenu();
	
	bool isLoopMenu = true;
	int input;

	while (isLoopMenu) {
		cout << endl;
		cout << "--------------------- Main Menu ---------------------" << endl;
		cout << "1. Tournament Registration & Player Queuing" << endl;
		cout << "2. Match Scheduling & Player Progression" << endl;
		cout << "3. Live Stream & Spectator Queue Management" << endl;
		cout << "4. Game Result Logging & Performance History" << endl;
		cout << "-1. Exit System" << endl;
		cin >> input;
		
		switch (input) {
		case 1:
			reg.openMenu();

			init();
			for (int i = 0; i < (sizeof(dummyPlayer) / sizeof(dummyPlayer[0])); i++) {
				dataPlayer[i] = new Player(stoi(dummyPlayer[i][0]), dummyPlayer[i][1], stoi(dummyPlayer[i][2]), stoi(dummyPlayer[i][3]), dummyPlayer[i][4]);
				numPlayer++;
			}

			for (int i = 0; i < numPlayer; i++) {
				registerPlayer->enQueue(dataPlayer[i]);
			}

			while (!registerPlayer->isEmpty()) {
				checkInPlayer->enQueue(registerPlayer->deQueue(), [](Player* p1, Player* p2) {return p1->getPlayerPriority() < p2->getPlayerPriority(); });
			}

			checkInPlayer->listQueue([](Player* p) {
				cout << p->getPlayerName() << " | " << to_string(p->getPlayerRating()) << " | " << to_string(p->getPlayerPriority()) << " | " << p->getPlayerUniversity() << endl;
				});

			TeamReg.openMenu();

			Teams->listQueue([](Team* t) { cout << t->getTeamName() << " | " << t->getTeamRating() << endl; });
			break;

		case 2:
			MatchDash.openMenu();

			if (Teams->getQueueLength() == 1) { 
				cout << "Game Finish Winner: " << Teams->peek()->getTeamName() << endl; 
				addTournamentDetails(Teams, PastTournaments);
			}
			break;

		case 3:
			specDashboard.openMenu();
			break;

		case 4:
			Logs.openMenu();
			break;

		case -1:
			isLoopMenu = false;
			cout << "Exiting System..." << endl;
			break;

		default:
			cout << "Please Select a correct input" << endl;
			cin.clear();
			cin.ignore(100, '\n');
			break;
		}
	}

}



