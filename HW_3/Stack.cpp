/* Assignment C++: 1
Author: Yuval Hendler, ID: 324180363
Author: Ori Sadek, ID: 211973011
*/

#include "Stack.h"
#include "iostream"
#include <climits>
using namespace  std;

Stack::Stack() {
	top = NULL;
}

Stack::~Stack() {
	while (!isEmpty()) {
		StackNode* ptr = top;
		top = top->get_next();
		delete ptr;
	}
}

void Stack::mannagePush() {
	int val;
	cout << "Please insert the new element:";
	cin >> val;
	this->push(val);
}

void Stack::push(int num) {
	StackNode* new_node = new StackNode(num);
	if (isEmpty()) {
		top = new_node;
	}
	else {
		new_node->set_next(top);
		top = new_node;
	}

}

bool Stack::isEmpty() const {
	if (top == NULL) {
		return true;
	}
	return false;
}

void Stack::pop() {
	if (this->isEmpty()) {
		cout << "Stack is empty" << endl;
	}
	else {
		StackNode* ptr = top;
		cout << "Removing " << ptr->get_data() << endl;
		top = top->get_next();
		delete ptr;
	}
}

int Stack::peek()const  //showing the top node data if exist
{
	if (top == NULL) {
		return INT_MIN;
	}
	return top->get_data();
}

