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

	void recentMatchResults() {
		Stack<MatchResult>* globalStack = matchDash.getResultStack();
		Stack<MatchResult>* clonedStack = globalStack;

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

		while (!playerQueue.isEmpty()) {
			RankedPlayer rp = playerQueue.dequeue();

			cout << left
				<< "| " << setw(10) << rp.player->getPlayerName()
				<< "| " << setw(8) << trim(rp.player->getPlayerUniversity())
				<< "| " << setw(10) << rp.player->getPlayerRating()
				<< "( " << rp.result << " )" << endl;
		}

	}

	void pastTournamentResults() {

	}

public:
	LogHistory(MatchDashboard& matchDash) : matchDash(matchDash) {}


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