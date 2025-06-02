#pragma once
#include <iostream>
#include "structure.hpp"
#include "PriorityQueueSpectator.hpp"

using namespace std;


class CircularQueueSpectatorOverflow {
private:
	Spectator* arr;
	int front, rear, count;
	int maxSize;

public:
	// Constructor
	

	CircularQueueSpectatorOverflow(int size) {
		arr = new Spectator[size];
		maxSize = size;
		count = 0;
		front = 0;
		rear = -1;
	}

	// Destructor
	//~CircularQueueSpectatorOverflow() {
	//	delete[] arr;
	//	cout << "CircularQueueSpectatorOverflow has been deleted!" << endl;
	//}

	// Check if the circular queue is empty
	bool isEmpty() {
		return count == 0;
	}

	// Check if the circular queue is full
	bool isFull() {
		return count == maxSize;
	}

	// Get the front element
	Spectator getFront() {
		// Circular queue is empty
		if (isEmpty()) {
			cout << "The circular queue is empty! No value retrieved!" << endl;
			return Spectator();
		}
		return arr[front];
	}

	// Get the rear element
	Spectator getRear() {
		// Circular queue is empty
		if (isEmpty()) {
			cout << "The circular queue is empty! No value retrieved!" << endl;
			return Spectator();
		}
		// int rear = (front + count - 1) % maxSize;
		return arr[rear];
	}

	// Insert an element at the rear
	void enqueue(Spectator spectator) {
		// Circular queue is full
		if (isFull()) {
			cout << "The circular queue is full! Cannot enqueue!" << endl;
			return;
		}
		// int rear = (front + count) % maxSize;
		rear = (rear + 1) % maxSize;
		arr[rear] = spectator;
		count++;
	}

	// Remove an element from the front
	Spectator dequeue() {
		// Circular queue is empty
		if (isEmpty()) {
			cout << "The circular queue is empty! Cannot dequeue!" << endl;
			return Spectator();
		}
		Spectator removing = arr[front];
		front = (front + 1) % maxSize;
		count--;
		return removing;
	}

	// Display all elements in the circular queue
	void displayCircularQueue() {
		cout << "Overflow Circular Queue: " << endl;
		for (int i = 0; i < count; i++) {
			int index = (front + i) % maxSize;
			cout << (i + 1) + "." << arr[index].getSpectatorID() << " " << arr[index].getSpectatorName() << endl;
		}
	}

};