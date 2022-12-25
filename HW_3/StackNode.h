/* Assignment C++: 1
Author: Yuval Hendler, ID: 324180363
Author: Ori Sadek, ID: 211973011
*/

class StackNode {
	int data;
	StackNode* next;
public:
	StackNode(int num = 0); //personal and default cons
	~StackNode(); //default dest
	int get_data() const;
	void set_next(StackNode* next);
	StackNode* get_next() const;

};