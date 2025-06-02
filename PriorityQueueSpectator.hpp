#pragma once
#include <iostream>
#include <string>
#include "structure.hpp"
#include "CircularQueueSpectatorOverflow.hpp"
using namespace std;

struct spectatorNode // Using doubly linked list
{
	Spectator spectatorData;
	spectatorNode* prevAddress;
	spectatorNode* nextAddress;

	// Node Constructor
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
	// Priority queue constructor
	PriorityQueueSpectator() {
		front = rear = NULL;
		size = 0;
	}

	// Destructor
	~PriorityQueueSpectator() {
		spectatorNode* temp = front;
		while (temp != nullptr) {
			spectatorNode* next = temp->nextAddress;
			delete temp;
			temp = next;
		}
		cout << "Spectator priority queue is deleted!" << endl;
	}

	// Create new spectator node 
	spectatorNode* CreateNewNode(Spectator spectatorData) {
		return new spectatorNode(spectatorData);
	}

	// Check whether the priority queue is empty
	bool isEmpty() {
		return (front == NULL && size == 0);
	}

	// Check whether the priority queue is full and has reached the max size of 35
	bool isFull() {
		return size == maxSize;
	}

	// Get the first spectator
	Spectator peek() {
		if (isEmpty()) {
			cout << "Priority queue is empty!" << endl;
			return Spectator();
		}
		return front->spectatorData;
	}

	// Get the current number of spectators in the priority queue
	int getSize() {
		return size;
	}

	int getMaxSize() {
		return maxSize;
	}

	// Insert the spectator to the end of the priority queue
	void enQueueToBack(Spectator spectatorData) {
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

	// Insert the spectator to the front of queue
	void enQueueToFront(Spectator spectatorData) {
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

	// Remove spectator from front
	Spectator deQueue() {
		if (isEmpty()) {
			cout << "Priority queue is empty!" << endl;
			return Spectator();
		}

		spectatorNode* current = front;
		Spectator data = current->spectatorData;

		front = front->nextAddress;
		if (front == nullptr) {
			rear = nullptr;
		}
		else {
			front->prevAddress = nullptr;
		}

		delete current;
		size--;
		return data;
	}

	// Display the whole priority queue
	void displaySpectatorPriorityQueue() {
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

	// Insert based on the priority
	void insertByPriority(Spectator addSpectator, CircularQueueSpectatorOverflow overflowQueue) {
		// Case 1: Queue is not full — insert as normal
		if (!isFull()) {
			insertByPriorityWithoutLimit(addSpectator);
			return;
		}

		// Case 2: Queue is full — check if new spectator has higher priority than rear
		if (addSpectator.getSpectatorPriority() < rear->spectatorData.getSpectatorPriority()) {
			// Remove rear (lowest priority)
			Spectator removed = removeRear();

			// Insert new high-priority spectator in correct place
			insertByPriorityWithoutLimit(addSpectator);

			// Send removed spectator to overflow queue
			if (!overflowQueue.isFull()) {
				overflowQueue.enqueue(removed);
			}
			else {
				cout << "Overflow queue full! Lost spectator: " << removed.getSpectatorID() << endl;
			}
		}
		else {
			// New spectator has lower or same priority, go to overflow
			if (!overflowQueue.isFull()) {
				overflowQueue.enqueue(addSpectator);
			}
			else {
				cout << "Overflow queue full! Lost spectator: " << addSpectator.getSpectatorID() << endl;
			}
		}
	}


	void insertByPriorityWithoutLimit(Spectator addSpectator) {
		spectatorNode* newnode = CreateNewNode(addSpectator);

		if (isEmpty()) {
			front = rear = newnode;
			size++;
			return;
		}

		if (addSpectator.getSpectatorPriority() < front->spectatorData.getSpectatorPriority()) {
			enQueueToFront(addSpectator);
			return;
		}

		if (addSpectator.getSpectatorPriority() >= rear->spectatorData.getSpectatorPriority()) {
			enQueueToBack(addSpectator);
			return;
		}

		spectatorNode* temp = front;
		while (temp->nextAddress != nullptr &&
			temp->nextAddress->spectatorData.getSpectatorPriority() <= addSpectator.getSpectatorPriority()) {
			temp = temp->nextAddress;
		}

		newnode->nextAddress = temp->nextAddress;
		if (temp->nextAddress != nullptr) {
			temp->nextAddress->prevAddress = newnode;
		}
		else {
			rear = newnode;
		}
		temp->nextAddress = newnode;
		newnode->prevAddress = temp;
		size++;
	}

	Spectator removeRear() {
		if (isEmpty()) return Spectator();

		spectatorNode* temp = rear;
		Spectator data = temp->spectatorData;

		if (front == rear) {
			front = rear = nullptr;
		}
		else {
			rear = rear->prevAddress;
			rear->nextAddress = nullptr;
		}

		delete temp;
		size--;
		return data;
	}

};
