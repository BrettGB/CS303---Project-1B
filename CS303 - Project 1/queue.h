//We were initially using a queue to complete our project, but we switched to a deque
//below is how our queue header file was/is implemented


//#pragma once
#include <cstddef>

template<typename Item_Type>
class queue {
private:
	// Insert implementation-specific data fields
	// Insert definition of Node here
#include "BookNode.h"
	// Data fields
	Node* front_of_queue;
	Node* back_of_queue;
	size_t num_items;


public:

	queue(BookNode* front_of_queue = NULL, BookNode* back_of_queue = NULL) :
		front_of_queue(front_of_queue), back_of_queue(back_of_queue), num_items(0) {}

	template<typename Item_Type>
	void push(const Item_Type& item) {
		if (front_of_queue == NULL) {
			back_of_queue = new BookNode(item, NULL);
			front_of_queue = back_of_queue;
			back_of_queue = new BookNode(item, NULL);
			front_of_queue = back_of_queue;
		}
		else {
			back_of_queue->next = new BookNode(item, NULL);
			back_of_queue = back_of_queue->next;
		}
		num_items++;
	}

	template<typename Item_Type>
	Item_Type& front() {
		return front_of_queue->data;

	}

	int size() {
		return num_items;
	}


	void pop() {
		BookNode* old_front = front_of_queue;
		front_of_queue = front_of_queue->next;
		if (front_of_queue == NULL) {
			back_of_queue = NULL;
		}
		delete old_front;
		num_items--;
	}

	int inc_wait() {
		wait_time++;
		return wait_time;
	}

	int inc_return() {
		retain_time++;
		return retain_time;
	}

	int
};