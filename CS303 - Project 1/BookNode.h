//Library Books, Node
#pragma once
#include <cstddef>
#include <string>

template <typename Item_Type>
struct BookNode {
	// Data Fields
	/** The data */
	Item_Type data;

	/** The pointer to the next node. */
	BookNode* next;
	string name;
	int wait_time = 0;
	int retain_time = 0;

	Date circultion_end = Date(2015, 1, 1, DateFormat::US);
	Date circulation_start = Date(2015, 1, 1, DateFormat::US);
	Date temp_date = Date(2015, 1, 1, DateFormat::US); //this is the last date that an update was made to the book (usually last date it was passed on)
	bool archived = false;
	bool in_circulation = false;
	deque<EmpNode<string>*> circulation;

	// Constructor
	/** Creates a new Node that points to another Node.
	@param data_item The data stored
	@param next_ptr Pointer to the Node that is
	pointed to by the new Node
	*/
	BookNode(const Item_Type& data_item = "", BookNode* next_ptr = NULL) :
		data(data_item), next(next_ptr) {}
};
