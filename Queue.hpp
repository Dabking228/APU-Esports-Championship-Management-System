#pragma once
#include <iostream>
#include <functional>
using namespace std;



template <typename T> class Queue {
protected:
	struct QueueNode {
		QueueNode* prev = nullptr;
		T* type;
		QueueNode* next = nullptr;
	};


	string QueueName;
	int size = 0; 
	int MAXSIZE = 0;

	QueueNode* createNewNode(T* type) {
		QueueNode* node = new QueueNode();
		node->prev = nullptr;
		node->type = type;
		node->next = nullptr;
		return node;
	}
	QueueNode* HEAD;
	QueueNode* TAIL;

public:
	Queue () {}

	Queue(string name) {
		HEAD = TAIL = nullptr;
		this->QueueName = name;
	}

	Queue(string name, int maxSize) {
		HEAD = TAIL = nullptr;
		this->QueueName = name;
		this->MAXSIZE = maxSize;
	}

	void enQueue(T* type) {
		if (size >= MAXSIZE && MAXSIZE != 0) { cout << "Queue is full;" << endl;return; }

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
	T* deQueue() {
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
		delete current;
	}

	// deQueue a specific item, put it into param
	T* deQueue(T* type) {
		if (HEAD == nullptr) { cout << "Noting to remove!" << endl; return nullptr; }
		if (type == nullptr) { cout << "Provided a nullptr! Will not proceed to deQueue" << endl; return nullptr; }

		QueueNode* current, *currPrev, *currNext = nullptr;
		current = HEAD;
		while (true) {
			if (current->type == type) {
				break;
			}
			current = current->next;
		}

		// if the queue is only one node, and remove that one node
		if (current->next == nullptr && current->prev == nullptr) {
			HEAD = TAIL = nullptr;
		}
		// if the pass-in type is the for the last node
		else if (current->next == nullptr) {
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
		delete current;
	}

	// deQueue by index
	T* deQueue(int index) {
		if (HEAD == nullptr) { cout << "Noting to remove!" << endl; return nullptr; }
		if (index < 0 || index > this->getQueueLength()) { return nullptr; }

		QueueNode* current = nullptr;
		current = HEAD;
		int calc = 1;
		if (index > 0 && index > 1) {
			do {
				current = current->next;
				calc++;
			} while (index != calc);
		}

		if (index == 1) { 
			current = HEAD; 
			HEAD = nullptr;
		}


		if(index == 0) { HEAD = current->next; }

		if (current->next == nullptr && index > 1) { 
			TAIL = current->prev; 
			current->prev->next = nullptr; 
		}
		
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
		delete current;
	}

	T* peek() {
		return HEAD->type;
	}

	/* uses lambda code to print any data
	* For example [](Type* t){ cout << " the data directly" << endl; }
	*/ 
	void listQueue(function<void (T*)> func) {
		QueueNode* temp = HEAD;

		while (temp != nullptr) {
			func(temp->type);
			temp = temp->next;
		}

		cout << "Queue End" << endl;
	}

	bool isEmpty() {
		if (size == 0) { return true; }
		else { return false; }
	}
	int getQueueLength() {return size;}

	/* uses lambda to search for the data, and return the data
	* pass into data, and uses lambda.
	* For example [](Type* t, string data){return bool;}
	*/
	T* getData(string data, function<bool (T*, string)> func) {
		QueueNode* temp = HEAD;

		while (temp != nullptr) {
			if (func(temp->type, data)) {
				return temp->type;
			}
			temp = temp->next;
		}

		if (temp == nullptr) {
			cout << "Cannot get Data from provided Data" << endl;
			return nullptr;
		}
	
	}




};