#pragma once
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include "EmpNode.h"
#include <deque>
#include "BookNode.h"


using namespace std;


class Library {
private:
	vector<string> books_circulate;
	vector<string> archive;
	deque<EmpNode<string>> employees;

	BookNode<string>* book_head = NULL;
	BookNode<string>* book_tail = NULL;

	EmpNode<string>* emp_tail = NULL;
	EmpNode<string>* emp_head = NULL;

public:
	void add_employee(string name){ //new way of initializing list
		//previous function was (void add_employee(EmpNode<string> **head, string name, int position)
		//if there is no head node
		if (emp_head == NULL) {	//if the employee linked list is empty, set the head to the new employee
			emp_head = new EmpNode<string>(name);
			emp_tail = emp_head;
		}

		//if there exists a head node
		else {
			emp_tail->next = new EmpNode<string>(name);
			emp_tail = emp_tail->next;
		}
	}

	int add_book(string book_name) {
		//will initialize the book's deque, but it will not give the book to the first employee
			//so the deque will be made, but it will not start circulating yet
				//the deque will be made, but it will not have any nodes/employees yet
				//the employees will be added when circulate_book is called


		//creates a new node for the new book, adds it to the linked list
		BookNode<string>* temp = new BookNode<string>(book_name);

		if (book_head == NULL) { //if the linked list is empty
			book_head = temp;		//set the temp node to the head/tail
			book_tail = book_head;
		}
		else { //else if the linked list is not empty, then set the temp node to the tail->next
			book_tail->next = temp;
			book_tail = book_tail->next;
		}

		return 0;
	}

	int circulate_book(string book_name, Date x) {

		//create a temporary BookNode pointer to the head of the books linked list
		BookNode<string>* book_temp = book_head;

		//traverse linked list to find the correct book (using book_name parameter)
		while (book_temp->data != book_name) { //potentially error if book_name is not entered in correctly
			book_temp = book_temp->next;
		}
		
		//create a temporary EmpNode pointer, set it to the head
		EmpNode<string>* emp_temp = emp_head;

		//initialized book's deque
		if (!book_temp->in_circulation) { //if book is not in circulation, change it to be in circulation
			book_temp->in_circulation = true;

			//this adds the employees to the book's deque
			while (emp_temp != NULL) {
				book_temp->circulation.push_back(emp_temp);
				emp_temp = emp_temp->next;
			}

			book_temp->circulation_start = x;  //sets the circulation start date with Date (x) parameter
			book_temp->temp_date = x;			//set the temporary date to the start date (x) as well
			pass_on(book_name, x, book_temp);	//calls the pass_on function so that the deque will be sorted according to waiting time
		}

		else { //book is already in circulation
			cout << endl << "ERROR: Book already in circulation." << endl;
		}


		//1. adds all the employees to the given book's queue  -done-
		//2. it will also order/sort the queue/employees based on waiting time
			//Idea: this function could call the "pass_on" function, 
			//since "pass_on" would be ordering/sorting the queue based on wait_time
			//and then the book will be given to the first employee
		//3. The Date parameter (x) is assigned to the circulation_start variable. 
			//also set (x) to the temp_date variable

		//make sure book is in vector
		//gives book to #1 in dequegiven date	
		return 0;
	}

	int pass_on(string book_name, Date c, BookNode<string>* book_temp = NULL) {

		if (book_temp == NULL) {
			book_temp = book_head;

			while (book_temp->data != book_name) {
				book_temp = book_temp->next;
			}
		}

		//check if the book is already archived, if it is then exit function
		if (book_temp->archived == true) {
			return 0;
		}
		
		int days_elapsed;

		//if the book is being put into circulation, then days elapsed will be 0 (zero)
		if (c == book_temp->circulation_start) {
			days_elapsed = c - book_temp->circulation_start;
		}
		else {
			days_elapsed = c - book_temp->temp_date;
		}

		//set the temporary date to the 'c' parameter (temporary date is used in the next pass_on call)
		book_temp->temp_date = c;

		//create a temporary EmpNode pointer equal to the deque's front EmpNode
		EmpNode<string>* temp_emp = book_temp->circulation.front();

		temp_emp->retain_time += days_elapsed;		//this increases retaining time for the employee with the book
		temp_emp = temp_emp->next;						//go to the next employee

		while (temp_emp != NULL) {
			temp_emp->wait_time += days_elapsed;	//increments waiting time for each subsequent employee
			temp_emp = temp_emp->next;		//move to the next employee
		}


		if (book_temp->circulation_start == c) {			//if book is being circulated for the first time (first call to circulate_book(book_name...))
		}
		else {			//else the book has already been circulated
			book_temp->circulation.pop_front(); //removes the employee who used to have the book
		}

		/*sorting method:
			1. create a new "temp" queue
			2. find node with largest waiting time then add it to front (push) of "temp" queue
				remove it from original queue
			3. keep doing this until the original list is empty*/

		deque<EmpNode<string>*> temp_deque;		//create a temporary deque
		deque<EmpNode<string>*>::iterator it;		//create iterators for the deque
		deque<EmpNode<string>*>::iterator it_temp;
		int index = 0;		//used to store the index of the iterator
		int temp_index = -1;	//used as a temporary index
		bool new_max = false;	//becomes true if a switch/new_max is found while iterating through the deque


		while (!book_temp->circulation.empty()) {		//while the book's deque is not empty

			temp_emp = book_temp->circulation.front();		//set the temporary EmpNode pointer to the deque's first node

			for (it = book_temp->circulation.begin(); it != book_temp->circulation.end(); ++it) {		//iterate through the deque
				++temp_index;		//increment the temporary index each time

				if (temp_emp->wait_time < (*it)->wait_time) {		//if a new max is found (using waiting time variable)
					temp_emp = *it;			//set the temporary pointer equal to the iterator's node

					new_max = true;
				}

				if (new_max) {		//if a new max was found
					index += temp_index;		//add the temp index to the index variable (the temp_index is the index of the new max value)
					temp_index = 0;		//set temp index to 0
					new_max = false;	//set new_max back to false
				}
			}
			
			//adds the employee with the maximum waiting time to the back of the temporary deque
			temp_deque.push_back(temp_emp);

			book_temp->circulation.erase(book_temp->circulation.begin()+index);		//this erases the employee with the max waiting time from the book's deque (uses beginning of the deque + the index value)
			
			//reseting variables
			index = 0;
			temp_index = -1;
			new_max = false;

		}

		//set the book's deque equal to the temporary deque (since the book's deque is now empty)
		book_temp->circulation = temp_deque;

		//if the deque is empty, then the book is in the archives
		if (book_temp->circulation.empty()) {
			book_temp->archived = true;
			return 0;
		}

		/*1. FIRST UPDATE WAITING AND RETAINING TIMES
			compare the Date paramter (c) to the temp_date variable within the library book's node
			the waiting time will be incremented by the difference between the Date (c) and the temp_date
			 waiting_time += (c - temp_date);
			retaining_time will also be updated (but only for the employee who was holding the book)
		2. this will order/sort the queue/employees based on wait_time FIRST (do this first)
		3. then the book will be pased on to the next employee (the one with the most/largest wait_time)
		4. then pop the previous employee
				do checks to make sure there is indeed a next employee
				if there is no next employee, the book will be passed on to the archive

		give book to next employee
		increment wait_time/retain_time
		if end of queue, pass book to archive*/
		return 0;
	}
};