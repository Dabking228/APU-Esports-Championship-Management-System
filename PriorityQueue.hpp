#pragma once
#include "Queue.hpp"
#include <iostream>
using namespace std;

template <typename T> class PriorityQueue : public Queue<T> {
private:
	bool checkUnique(T* type) {
		typename Queue<T>::QueueNode* temp = this->HEAD;

		while (temp != nullptr) {
			
			if (temp->type == type) {
				return true;
			}

			temp = temp->next;
		}

		return false;
	}
public:
	PriorityQueue() : Queue<T>() {}

	PriorityQueue(string name) : Queue<T>(name) {};

	PriorityQueue(string name, int maxSize) : Queue<T>(name, maxSize) {};

	void enQueue(T* type, function<bool(T*,T*)> func) {
		typename Queue<T>::QueueNode* node = this->createNewNode(type);

		if (this->HEAD == nullptr) {
			this->HEAD= this->TAIL = node;
		}
		else {
			if (this->HEAD->next == nullptr) {
				typename Queue<T>::QueueNode* curr = this->HEAD;
				if (func(node->type, this->HEAD->type)) {
					this->HEAD = node;
					node->next = curr;
					curr->prev = node;
					this->TAIL = curr;
				}
				else {
					this->HEAD->next = node;
					node->prev = this->HEAD;
					this->TAIL = node;
				}

			}
			else {
				bool compare = true;
				typename Queue<T>::QueueNode* curr = this->HEAD;
				do {
					if (func(node->type, curr->type)) {
						node->next = curr;
						node->prev = curr->prev;
						if (curr->prev != nullptr) { curr->prev->next = node; }
						else { this->HEAD = node; }
						curr->prev = node;
						compare = false;
					}
					curr = curr->next;
					if (curr == nullptr && compare) {
						this->TAIL->next = node;
						node->prev = this->TAIL;
						this->TAIL = node;
						compare = false;
					}
				} while (compare);			
			}
		}
		this->size++;
	}

	void enQueue(T* type, function<bool(T*, T*)> func, bool isUnique) {
		if (isUnique == false) { this->enQueue(type, func);  }

		if (checkUnique(type)) { cout << "couldnt add to queue" << endl; return; }

		this->enQueue(type, func);
	}

	typename PriorityQueue<T>::QueueNode* getHead() const { return this->HEAD; }
};