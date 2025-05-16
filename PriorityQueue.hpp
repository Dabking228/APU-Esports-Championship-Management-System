#pragma once
#include <iostream>
#include "Queue.hpp"
using namespace std;

template <typename T> class PriorityQueue : public Queue<T>{

public:
	PriorityQueue(){}

	PriorityQueue(string name){
		Queue<T>::QueueName = name;
	}

	void enQueue(T type, function<bool(T,T)> func) {
		QueueNode<T>* node = Queue<T>::createNewNode(type);
		
		if (Queue<T>::HEAD == nullptr) {
			Queue<T>::HEAD = Queue<T>::TAIL = node;
		}
		else {
			if (Queue<T>::HEAD->next == nullptr) {
				Queue<T>::HEAD->next = node;
				node->prev = Queue<T>::HEAD;
				Queue<T>::TAIL = node;
			}
			else {
				bool compare = true;
				QueueNode<T>* curr = Queue<T>::HEAD;
				do {
					if (func(curr->type, node->type)) {
						node->next = curr;
						node->prev = curr->prev;
						curr->prev->next = node;
						curr->prev = node;
						compare = false;
					}
					curr = curr->next;
					if (curr == nullptr) {
						Queue<T>::TAIL->next = node;
						node->prev = Queue<T>::TAIL;
						Queue<T>::TAIL = node;
						compare = false;
					}
				} while (compare);

				
			}
		};
	}
};