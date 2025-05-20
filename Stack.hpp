#pragma once
#include <iostream>
using namespace std;

template <typename T> class Stack {

	struct StackNode {
		StackNode* prev;
		T* type;
		StackNode* next;
	};

	StackNode* createNewNode(T* type) {
		StackNode* node = new StackNode();
		node->prev = nullptr;
		node->type = type;
		node->next = nullptr;

		return node;
	}

	string StackName;
	StackNode* HEAD;
	StackNode* TAIL;
	int MAXSIZE = 0;
	int size = 0;

public:
	Stack(){}

	Stack(string name) {
		this->StackName = name;
		this->MAXSIZE = -1; 
	}

	Stack(string name, int size) {
		this->StackName = name;
		this->MAXSIZE = size;
	}

	T* peek() {
		if(isEmpty()){ cout << "Stack is empty! Peak Failed" << endl; return nullptr; }
		return TAIL->type;
	}

	void push(T* type) {
		if (size >= MAXSIZE) { cout << "Stack is full;" << endl;return; }

		StackNode* node = createNewNode(type);

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

	T* pop() {
		if (this->isEmpty()) { cout << "Stack is empty!" << endl; return nullptr; }

		StackNode* curr = TAIL;
		T* val = curr->type;

		if (HEAD == TAIL) {
			HEAD = TAIL = nullptr;
		}
		else {
			TAIL = TAIL->prev;
			TAIL->next = nullptr;
		}

		// reduce size and delete node
		size--;
		delete curr;

		return val;
	}

	bool isEmpty() { if (size == 0) return true; }
	int getStackLength() { return size; }
};
