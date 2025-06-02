#pragma once
#include <iostream>
#include <string>
#include "structure.hpp"
using namespace std;

struct spectatorNode //using doubly linked list
{
	Spectator spectatorData;
	spectatorNode* prevAddress;
	spectatorNode* nextAddress;

	spectatorNode(Spectator spectatorData) {
		this->spectatorData = spectatorData;
		prevAddress = nullptr;
		nextAddress = nullptr;
	}
};

class PriorityQueueSpectator {
	spectatorNode* front, * rear;
	int size = 0;
	const int maxSize = 35; // The first 35 spectators to enter the spectating area

public:
	PriorityQueueSpectator() {
		front = rear = NULL;
		size = 0;
	}

	~PriorityQueueSpectator() {
		spectatorNode* temp = front;
		while (temp != nullptr) {
			spectatorNode* next = temp->nextAddress;
			delete temp;
			temp = next;
		}
		cout << "Spectator priority queue is deleted!" << endl;
	}

	spectatorNode* CreateNewNode(Spectator spectatorData) {
		return new spectatorNode(spectatorData);
	}

	bool isEmpty() {
		return (front == NULL && size == 0);
	}

	bool isFull() {
		return size == maxSize;
	}

	Spectator peek() {
		if (isEmpty()) {
			cout << "Priority queue is empty!" << endl;
		}
		return front->spectatorData;
	}

	void enQueue(Spectator spectatorData) { // normal process: add the spectator to the end of the priority queue
		if (isFull()) {
			cout << "Priority queue is full!" << endl;
			return;
		}

		spectatorNode* newNode = CreateNewNode(spectatorData);
		if (isEmpty()) {
			front = rear = newNode;
		}
		else {
			rear->nextAddress = newNode;
			newNode->prevAddress = rear;
			rear = newNode;
		}
		size++;
	}

	void enQueueToFront(Spectator spectatorData) { // insert spectator to the front of queue
		if (isFull()) {
			cout << "Priority queue is full!" << endl;
			return;
		}

		spectatorNode* newNode = CreateNewNode(spectatorData);
		if (isEmpty()) {
			front = rear = newNode;
		}
		else {
			newNode->nextAddress = front;
			front->prevAddress = newNode;
			front = newNode;
		}
		size++;
	}

	spectatorNode* DeQueue(int position) { 
		if (isEmpty()) {
			cout << "Priority queue is empty!" << endl;
			return nullptr;
		}

		spectatorNode* current = nullptr;
		if (position == 1) { // First spectator
			current = front;
			front = front->nextAddress;
			if (front == nullptr) {
				rear = nullptr;
			}
			else {
				front->prevAddress = nullptr;
			}
		}
		else if (position == size) { // Last spectator
			current = rear;
			rear = rear->prevAddress;
			if (rear == nullptr) {
				front = nullptr;
			}
			else {
				rear->nextAddress = nullptr;
			}
		}
		else if (position < 1 || position > size) { // Position is out of range
			return current;
		}
		else { // Spectator is in the middle
			current = front->nextAddress;
			int currentIndex = 2;

			while (currentIndex != position) {
				current = current->nextAddress;
				currentIndex++;
			}
			current->prevAddress->nextAddress = current->nextAddress;
			current->nextAddress->prevAddress = current->prevAddress;
		}
		current->nextAddress = nullptr;
		current->prevAddress = nullptr;
		size--;
		return current;
	}

	

	void displaySpectatorPriorityQueue() { // Priority process
		if (isEmpty()) {
			cout << "Priority queue is empty!" << endl;
			return;
		}
		cout << "Spectator priority queue contains " << size << " spectators: ";
		spectatorNode* current = front;
		while (current != nullptr) {
			cout << current->spectatorData.getSpectatorID() << " " << current->spectatorData.getSpectatorName() << ", ";
			current = current->nextAddress;
		}
		cout << endl;
	}

	void MoveNthFront(int position) { 
		spectatorNode* newnode = DeQueue(position); // delete from the specific location
		if (newnode != nullptr) {
			enQueueToFront(newnode->spectatorData);
		}
	}


};
