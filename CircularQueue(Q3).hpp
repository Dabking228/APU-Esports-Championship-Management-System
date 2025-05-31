#pragma once
#include <iostream>
using namespace std;

template <typename T>
class CircularQueue {
private:
    int front, rear, size;
    int capacity;
    T* arr;

public:
    CircularQueue(int maxSize = 30) {
        capacity = maxSize;
        arr = new T[capacity];
        front = -1;
        rear = -1;
        size = 0;
    }

    ~CircularQueue() {
        delete[] arr;
    }

    bool isFull() { 
        return size == capacity;
    }

    bool isEmpty() const {
        return size == 0;
    }

    void enqueue(T item) {
        if (isFull()) {
            cout << "Queue is full. Cannot enqueue.\n";
            return;
        }

        if (front == -1) front = 0;

        rear = (rear + 1) % capacity;
        arr[rear] = item;
        size++;
    }

    T dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty. Cannot dequeue.\n";
            return nullptr;
        }

        T item = arr[front];
        front = (front + 1) % capacity;
        size--;

        if (size == 0) {
            front = -1;
            rear = -1;
        }

        return item;
    }

    void printQueue() {
        if (isEmpty()) {
            cout << "Queue is empty.\n";
            return;
        }

        cout << "Circular Queue: ";
        for (int i = 0; i < size; i++) {
            int index = (front + i) % capacity;
            cout << arr[index]->getPlayerName() << " ";
        }
        cout << endl;
    }

    int getSize() {
        return size;
    }

    CircularQueue<T> clone() const {
        CircularQueue<T> newQueue(capacity);

        if (isEmpty()) return newQueue;

        for (int i = 0; i < size; ++i) {
            int index = (front + i) % capacity;
            newQueue.enqueue(arr[index]);
        }

        return newQueue;
    }

};