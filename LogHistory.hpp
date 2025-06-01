#include <iostream>
#include <iomanip>
#include "Stack.hpp"
#include "MatchDetails.hpp"
#include "structure.hpp"
#include "Utils.hpp"
using namespace std;

class LogHistory {

	Stack<Player>* players;
	MatchDashboard& matchDash;
	PriorityQueue<TournamentDetails> PastTournaments;

	void recentMatchResults() {
		Stack<MatchResult>* globalStack = matchDash.getResultStack();
		Stack<MatchResult>* clonedStack = globalStack;

		if (globalStack->isEmpty()) {
			cout << "No matches ended yet!" << endl;
			return;
		}

		while (!clonedStack->isEmpty()) {
			MatchResult* result = clonedStack->pop();

			cout << result->getMatchName() << " | "
				<< result->getTeam1() << " ("
				<< result->getScore1() << ") VS "
				<< result->getTeam2() << " ("
				<< result->getScore2() << ") Winner: "
				<< result->getWinner() << " (Players: "
				<< result->getPlayerList() << ") | Highlight: "
				<< result->getHighlight() << endl;

			delete result;
		}

		delete clonedStack;
	}

	void playerPerformance() {
		CircularQueue<RankedPlayer>& playerQueue = matchDash.getPlayerQueue();
		CircularQueue<RankedPlayer> clonedQueue = playerQueue.clone();

		if (playerQueue.isEmpty()) {
			cout << "No players won or lost yet!" << endl;
			return;
		}

		while (!clonedQueue.isEmpty()) {
			RankedPlayer rp = clonedQueue.dequeue();

			cout << left
				<< "| " << setw(10) << rp.player->getPlayerName()
				<< "| " << setw(8) << trim(rp.player->getPlayerUniversity())
				<< "| " << setw(10) << rp.player->getPlayerRating()
				<< "( " << rp.result << " )" << endl;
		}

	}

	void pastTournamentResults() {

		auto* curr = PastTournaments.getHead();

		while (!PastTournaments.isEmpty()) {
			TournamentDetails* t = PastTournaments.deQueue();

			cout << "----------------------------------------" << endl;

			cout << "Date: " << t->getDate() << endl;
			cout << "Venue: " << t->getVenue() << endl;
			cout << "Name: " << t->getName() << endl;
			cout << "Duration: " << t->getAvgDuration() << endl;
			cout << "Winner: " << t->getWinner() << endl;
			cout << "Team Rating: " << t->getTeamRating() << endl;
			cout << "Total Viewers: " << t->getTotalViewers() << endl;
			cout << "Players: " << endl;
			cout << "  " << t->getPlayer1() << " - " << t->getUni1() << endl;
			cout << "  " << t->getPlayer2() << " - " << t->getUni2() << endl;
			cout << "  " << t->getPlayer3() << " - " << t->getUni3() << endl;
			cout << "  " << t->getPlayer4() << " - " << t->getUni4() << endl;
			cout << "  " << t->getPlayer5() << " - " << t->getUni5() << endl;

		}

		cout << "----------------------------------------" << endl << endl;
	}

public:
	LogHistory(MatchDashboard& matchDash, PriorityQueue<TournamentDetails> PastTournaments) : matchDash(matchDash), PastTournaments(PastTournaments){}


	void openMenu() {
		bool isLoopMenu = true;
		int input;

		while (isLoopMenu) {
			cout << "--- View Statistics ---" << endl;
			cout << "1. Recent Match Results" << endl;
			cout << "2. Player Performance " << endl;
			cout << "3. Past Tournament Results " << endl;
			cout << "-1. Back to Menu" << endl;
			cin >> input;
			switch (input) {
			case 1:
				recentMatchResults();
				break;
			case 2:
				playerPerformance();
				break;
			case 3:
				pastTournamentResults();
				break;
			case -1:
				isLoopMenu = false;
				cout << "Back to dashboard" << endl;
				break;
			default:
				cout << "Please Select a correct input" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				break;
			}
		}
	}


};