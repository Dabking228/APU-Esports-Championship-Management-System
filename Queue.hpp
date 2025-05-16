#pragma once
#include <iostream>
using namespace std;

template <typename T> class Queue {
	
private:
	struct QueueNode {
		QueueNode* prev;
		T type;
		QueueNode* next;
	};

	QueueNode* HEAD;
	QueueNode* TAIL;
	string QueueName;
	int size = 0;

	QueueNode* createNewNode(T type) {
		QueueNode* node = new QueueNode();
		node->type = type;
		node->next = nullptr;
		node->prev = nullptr;
		return node;
	}

public:
	Queue(string name) {
		HEAD = TAIL = nullptr;
		this->QueueName = name;
	}

	void enQueue(T type) {
		QueueNode* node = this->createNewNode(type);

		if (HEAD == nullptr) {
			HEAD = TAIL = node;
		}
		else {
			TAIL->next = node;
			node->prev = TAIL;
			TAIL = node;
		}

		size++;
	}

	// This deQueue is only applied for the head of the queue
	T deQueue() {
		if (HEAD == nullptr) { cout << "Noting to remove!" << endl; return NULL; }

		QueueNode* current = nullptr;
		current = HEAD;
		HEAD = current->next;
		if (HEAD == nullptr) {
			TAIL = nullptr;
		}
		else {
			HEAD->prev = nullptr;
		}

		current->next = nullptr;
		current->prev = nullptr;
		size--;

		return current->type;
	}

	// deQueue a specific item, put it into param
	T deQueue(T type) {
		if (HEAD == nullptr) { cout << "Noting to remove!" << endl; return NULL; }

		QueueNode* current, *currPrev, *currNext = nullptr;
		current = HEAD;
		while (true) {
			if (current->type == type) {
				break;
			}
			current = current->next;
		}

		// if the pass-in type is the for the last node
		if (current->next == nullptr) {
			TAIL = current->prev;
			TAIL->next = nullptr;
		}
		// if the pass-in is the first node
		else if (current->prev == nullptr) {
			HEAD = current->next;
			HEAD->prev = nullptr;
		}
		// the node past in is the middle
		else {
			currNext = current->next;
			currPrev = current->prev;
			currNext->prev = currPrev;
			currPrev->next = currNext;
		}

		current->next = nullptr;
		current->prev = nullptr;
		size--;

		return current->type;
	}

	void listQueue() {
		QueueNode* temp = HEAD;

		while (temp != nullptr) {
			cout << "Queue: " << temp->type << endl;
			temp = temp->next;
		}

		cout << "Queue End" << endl;
	}

	bool isEmpty() {
		if (HEAD == nullptr && TAIL == nullptr) {
			return true;
		}
		else { return false; }
	}

	int getQueueLength() {
		return size;
	}
};