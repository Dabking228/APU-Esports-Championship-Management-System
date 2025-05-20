#pragma once
#include "Queue.hpp"
#include <iostream>
using namespace std;

template <typename T> class PriorityQueue : public Queue<T> {

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
				this->HEAD->next = node;
				node->prev = this->HEAD;
				this->TAIL = node;
			}
			else {
				bool compare = true;
				typename Queue<T>::QueueNode* curr = this->HEAD;
				do {
					if (func(curr->type, node->type)) {
						node->next = curr;
						node->prev = curr->prev;
						if (curr->prev != nullptr) { curr->prev->next = node; }
						else { this->HEAD = node; }
						curr->prev = node;
						compare = false;
					}
					curr = curr->next;
					if (curr == nullptr) {
						this->TAIL->next = node;
						node->prev = this->TAIL;
						this->TAIL = node;
						compare = false;
					}
				} while (compare);

				
			}
		};
	}
};