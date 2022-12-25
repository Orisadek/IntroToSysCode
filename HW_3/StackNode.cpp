/* Assignment C++: 1
Author: Yuval Hendler, ID: 324180363
Author: Ori Sadek, ID: 211973011
*/
#include "iostream"
#include "StackNode.h"
using namespace  std;



// set up the main constractor with init data
StackNode::StackNode(int num) {
	data = num;
	next = NULL;
}
StackNode::~StackNode() {}

int StackNode::get_data() const {
	int x = this->data;
	return x;
}

void StackNode::set_next(StackNode* next) {
	this->next = next;
}

StackNode* StackNode::get_next()const {
	StackNode* p;
	p = this->next;
	return p;
}
