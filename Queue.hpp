#pragma once
#include <iostream>
#include <functional>
using namespace std;

template <typename T> struct QueueNode {
	QueueNode* prev = nullptr;
	T* type;
	QueueNode* next = nullptr;
};

template <typename T> class Queue {
protected:
	string QueueName;
	int size = 0;
	int MAXSIZE = 0;

	QueueNode<T>* createNewNode(T* type) {
		QueueNode<T>* node = new QueueNode<T>();
		node->prev = nullptr;
		node->type = type;
		node->next = nullptr;
		return node;
		}
	QueueNode<T>* HEAD;
	QueueNode<T>* TAIL;

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
		QueueNode<T>* node = this->createNewNode(type);

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

		QueueNode<T>* current = nullptr;
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
	T* deQueue(T type) {
		if (HEAD == nullptr) { cout << "Noting to remove!" << endl; return NULL; }

		QueueNode<T>* current, *currPrev, *currNext = nullptr;
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
		delete current;
	}

	T* front() {
		return HEAD->type;
	}


	void listQueue(function<string (T*)> func) {
		QueueNode<T>* temp = HEAD;

		while (temp != nullptr) {

			cout << "Queue: " << func(temp->type) << endl;
			temp = temp->next;
		}

		cout << "Queue End" << endl;
	}

	bool isEmpty() { if (size == 0) return true; }
	int getQueueLength() {return size;}


	/*
	Unused code
	Part of unused code due to adding new stuff into it.
	keep this as a point of reference
	
	void listQueue() {
		QueueNode* temp = HEAD;

		while (temp != nullptr) {
			cout << "Queue: " << temp->type << endl;
			temp = temp->next;
		}

		cout << "Queue End" << endl;
	}

	*/



};