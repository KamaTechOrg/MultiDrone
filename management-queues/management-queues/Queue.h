#pragma once
#include <iostream>
#include <stdexcept>
#include <mutex>
#include "Message.h"
#include "Priority.h"
#include <vector>
using namespace std;

// Node structure for the doubly linked list
struct Node {
	Message data;
	Node* next;
	Node* prev;

	Node(Message data) : data(data), next(nullptr), prev(nullptr) {}
};

typedef void (*FuncPtr)();

class Queue {
private:
	vector<FuncPtr> pointersToFunctions;

	Node* head;
	Node* tail;
	Priority priority;
	int weight;
	int currentWeight;
	int maxOfMessages;
	int numOfMessages;
	std::mutex mtx;

	void clear();
	//void copyFrom(const Queue& other);

public:
	Queue(Priority priority = Priority::Low) : head(nullptr), tail(nullptr), priority(priority) {}

	// Destructor to clean up the allocated memory
	~Queue();

	Queue(const Queue& other)  {
		this->priority = other.priority;
		head = other.head;
		tail = other.tail;
		weight = other.weight;
		currentWeight = other.currentWeight;
		maxOfMessages = other.maxOfMessages;
		numOfMessages = other.numOfMessages;
	}

	Queue& operator=(const Queue& other);

	void push(Message data);

	Message pop();

	Node* pick(int index);

	Message top() const;

	int pass() const;

	bool isEmpty() const;

	Priority GetPriority() const;

	void setPriority(Priority newPriority);

	int GetSize();

	void DecreaseWeight();

	int GetCurrentWeight() const;

	void Handler();
};