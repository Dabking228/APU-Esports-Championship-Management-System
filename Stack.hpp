#pragma once
#include <iostream>
using namespace std;

template <typename T> class Stack {


private:
	struct StackNode {
		StackNode* prev;
		T* type;
		StackNode* next;
	};

	StackNode* createNewNode(T type) {
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
		return TAIL->type;
	}

	void push(T type) {
		StackNode* node = createNewNode(type);

		if (HEAD == nullptr) {
			HEAD = TAIL = node;
		}
		else {
			TAIL->next = node;
			node->prev = TAIL;
			TAIL = node
		}

		size++;
	}

	T* pop() {
		if (HEAD == nullptr || TAIL == nullptr) { cout << "Stack is empty!" << endl; return nullptr; }

		StackNode* curr = TAIL;
		TAIL = TAIL->prev;
		curr->next = nullptr;
		size--;

		return curr->type;
		delete curr;
	}

	bool isEmpty() {
		if ((HEAD == nullptr || TAIL == nullptr) && size = > 0) { return true; }
	}
		
	int getStackLength() { return size; }
};
