//Employees, Node0
#pragma once
#include <cstddef>
#include <string>

template <typename Item_Type>
struct EmpNode {

	// Data Fields
	/** The data */
	Item_Type data;

	/** The pointer to the next node. */
	EmpNode* next;
	string name;
	int wait_time = 0;
	int retain_time = 0;

	// Constructor
	EmpNode(const Item_Type& data_item = "", EmpNode* next_ptr = NULL) :
		data(data_item), next(next_ptr) {}

	bool operator() (Item_Type wait_time, Item_Type wait_time_2) { return (wait_time < wait_time_2); }

};