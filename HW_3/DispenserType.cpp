/* Assignment C++: 1
   Author: Yuval Hendler, ID: 324180363
   Author: Ori Sadek, ID: 211973011
*/
#include "DispenserType.h"

DispenserType::DispenserType() {} //Constructor

DispenserType::DispenserType(int numberOfItems, int cost) { //Constructor
	this->numberOfItems = numberOfItems; //using this because same vars names
	this->cost = cost;
}

DispenserType::~DispenserType() {}; //Destructor

int DispenserType::getNoOfItems() const { //get the number of juice type
	return numberOfItems;
}

int DispenserType::getCost() const { //get the cost of juice type
	return cost;
}

void DispenserType::makeSale() { //reduce the number of juice type in one
	numberOfItems--;
}