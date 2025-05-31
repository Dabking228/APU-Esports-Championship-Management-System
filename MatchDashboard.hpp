#include <iostream>
#include "Stack.hpp"
#include "MatchDetails.hpp"
#include "PriorityQueue.hpp"
#include "CircularQueue(Q3).hpp"
#include "structure.hpp"
using namespace std;

extern const int MAXTEAM;

class MatchDashboard {
	bool isLoopMenu;
	int input = -100;

	int numOfMatch = 0;
	PriorityQueue<Team>* Teams;
	Stack<Team>* TourStack= new Stack<Team>();
	Stack<Team>** VsStack;
	MatchDetails** MatchDetail;
	Stack<MatchResult>* resultStack = new Stack<MatchResult>();
	CircularQueue<Player*> playerQueue;

	void showMenu() {
		cout << "--- Matchmaking Dashboard ---" << endl;
		cout << "1. Start Matching" << endl;
		cout << "2. Check Ongoing Match Detail" << endl;
		cout << "3. Next Game" << endl;
		cout << "4. Check All Match" << endl;
		cout << "-1. Return to Menu" << endl;
	}

	void checkOngoingMatch() {
		if (numOfMatch == 0) { cout << "Match not started" << endl; return; }

		bool isLoop = true;
		int choice = -100;
		
		// bug here
		cout << "--- Ongoing Match Details ---" << endl;
		for (int i = 0; i < numOfMatch; i++) {
			if (MatchDetail[i]->isMatchFinish()) { continue; }
			cout << i+1 << ". " << MatchDetail[i]->getMatchName() << endl;
		}


		cout << "-1. Return to menu" << endl;
		while (isLoop) {
			cin >> choice;
			if (choice == -1) { isLoop = false; break; }
			if(choice < 1 || choice > numOfMatch){}
			if (MatchDetail[choice - 1]->isMatchFinish()) { cout << "This Match is completed" << endl; isLoop = false; break; }
			MatchDetail[choice - 1]->openMenu();
			return;
		}
	}

	void checkAllMatch() {
		if (numOfMatch == 0) { cout << "Match not started" << endl; return; }

		bool isLoop = true;
		int choice = -100;

		cout << "--- Ongoing Match Details ---" << endl;
		for (int i = 0; i < numOfMatch; i++) {
			cout << i + 1 << ". " << MatchDetail[i]->getMatchName() << endl;
		}


		cout << "-1. Return to menu" << endl;
		while (isLoop) {
			cin >> choice;
			if (choice == -1) { isLoop = false; break; }
			if (choice < 1 || choice > numOfMatch) {}

			MatchDetail[choice - 1]->openMenu();
			return;
		}
	}

	void assignMatch() {
		if (numOfMatch != 0) { cout << "Match started" << endl; return; }
		if (Teams->getQueueLength() == 1) { cout << "Match is either finish/ 1 team only" << endl; return; }
		if (Teams->getQueueLength() < MAXTEAM) { cout << "Not enough Teams to start" << endl; return; }

		while (!this->Teams->isEmpty()) {
			Team* temp1 = this->Teams->deQueue();
			Team* temp2 = this->Teams->deQueue(this->Teams->getQueueLength());

		/*	cout << temp1->getTeamName() << endl;
			cout << temp2->getTeamName() << endl;*/

			TourStack->push(temp1);
			TourStack->push(temp2);
		}
		
		numOfMatch = TourStack->getStackLength() / 2;
		VsStack = new Stack<Team>*[numOfMatch];
		MatchDetail = new MatchDetails*[numOfMatch];

		for (int i = 0; i < numOfMatch; i++) {
			VsStack[i] = new Stack<Team>(2);


			VsStack[i]->push(TourStack->pop());
			VsStack[i]->push(TourStack->pop());

			MatchDetail[i] = new MatchDetails();
			MatchDetail[i]->setStack(VsStack[i]);
		}


		cout << "Match is now started" << endl;
	}

	void nextGame() {
		bool allFinish = true;
		for (int i = 0; i < numOfMatch; i++) {
			if (!MatchDetail[i]->isMatchFinish()) {
				allFinish = false;
			}
		}

		if (!allFinish || numOfMatch == 0) { cout << "Matches not yet finish" << endl; return; }
		
		for (int i = 0; i < numOfMatch; i++) {

			//requeue all winner
			Team* loser = MatchDetail[i]->getLoser();
			Team* winner = MatchDetail[i]->getWinner();
			Teams->enQueue(winner, [](Team* t1, Team* t2) {return t1->getTeamRating() < t2->getTeamRating();});
			
			//add rating to winners, reduce rating to losers
			for (int i = 1; i <= 5; ++i) {

				//winner
				Player* p = winner->getPlayer(i);
				if (p == nullptr) continue;

				int rating = p->getPlayerRating();
				rating = rating + 100;
				p->setPlayerRating(rating);

				if (playerQueue.isFull()) {
					playerQueue.dequeue();
				}

				playerQueue.enqueue(p);

				//loser
				Player* p2 = loser->getPlayer(i);
				if (p2 == nullptr) continue;

				rating = p->getPlayerRating();
				rating = rating - 100;
				p2->setPlayerRating(rating);

				if (playerQueue.isFull()) {
					playerQueue.dequeue();
				}

				playerQueue.enqueue(p);

			}

			//add match detail to stack
			Team* t1 = MatchDetail[i]->getT1Data();
			Team* t2 = MatchDetail[i]->getT2Data();
			int score1 = MatchDetail[i]->getT1Score();
			int score2 = MatchDetail[i]->getT2Score();

			string team1 = t1->getTeamName();
			string team2 = t2->getTeamName();
			string matchName = MatchDetail[i]->getMatchName();
			string winningTeam = winner->getTeamName();

			string playersList;
			int playerNum = 0;
			string MVP;

			//retrieve players for winning team
			for (int i = 1; i <= 5; ++i) {
				Player* p = winner->getPlayer(i);
				if (p == nullptr) continue;

				if (!playersList.empty()) {
					playersList += ", ";  //add comma separator if not first player
				}

				playersList += p->getPlayerName();
				playerNum++;
			}

			srand(static_cast<unsigned int>(time(nullptr)));

			//randomly picks a player as MVP
			if (playerNum == 0) {
				MVP = "No MVP";
			}
			else {
				int randomIndex = (rand() % playerNum) + 1;
				MVP = t1->getPlayer(randomIndex)->getPlayerName() + " is MVP!";
			}

			MatchResult* result = new MatchResult(matchName, team1, score1, team2, score2, winningTeam, playersList, MVP);
			resultStack->push(result);
			
			delete MatchDetail[i];
		}

		//delete the array and reset numofmatch
		delete[] MatchDetail;
		numOfMatch = 0;

		assignMatch();
	}

public:
	MatchDashboard(PriorityQueue<Team>* teams) {
		this->Teams = teams;
	}

	void openMenu() {
		isLoopMenu = true;
		while (isLoopMenu) {
			showMenu();
			cin >> input;
			switch (input) {
			case 1:
				assignMatch();
				break;
			case 2:
				checkOngoingMatch();
				break;
			case 3:
				nextGame();
				break;
			case 4:
				checkAllMatch();
				break;
			case -1:
				isLoopMenu = false;
				break;
			default:
				cout << "Please Select a correct input" << endl;
				cin.clear();
				cin.ignore(1, '\n');
				break;
			}
		}
			
	}


	MatchDetails** getMatchDetail() {
		return this->MatchDetail;
	}

	int getNumOfMatch() {
		return this->numOfMatch;
	}

	Stack<MatchResult>* getResultStack() {
		return resultStack;
	}

	CircularQueue<Player*>& getPlayerQueue() {
		return playerQueue;
	}
};