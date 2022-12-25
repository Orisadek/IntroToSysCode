/* Assignment C++: 1
Author: Yuval Hendler, ID: 324180363
Author: Ori Sadek, ID: 211973011
*/
#include "StackNode.h"

class Stack {
	StackNode* top;
public:
	void mannagePush();
	Stack(); //default cons
	~Stack(); //default dest
	void push(int num);
	void pop();
	bool isEmpty() const;
	int peek() const;

};