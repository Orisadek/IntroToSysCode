/* Assignment C++: 1
Author: Yuval Hendler, ID: 324180363
Author: Ori Sadek, ID: 211973011
*/

#include "VendingMachine.h"
#include <iostream>
using namespace std;

VendingMachine::VendingMachine() :orange(10, 45), carrot(5, 50), pomegranate(4, 75) {} //Constructor

VendingMachine::~VendingMachine() {}; //Destructor

void VendingMachine::mannageSell(DispenserType& juiceType) {
	int sum = 0;
	int times = 0;
	//the juice type isnt available
	if (juiceType.getNoOfItems() == 0) {
		cout << "Sorry, this item is sold out.\n";
	}
	else {
		//ask for the juice sum (less then 2 times)
		while (sum < juiceType.getCost() && times < 2) {
			times++;
			int sumTmp;
			cout << "Please deposit ";
			cout << juiceType.getCost() - sum;
			cout << " cents\n";
			cin >> sumTmp;
			sum = sum + sumTmp;
		}
		if (sum >= juiceType.getCost()) { // make sure the sum was payed
			juiceType.makeSale(); //remove one from stock
			counter.acceptAmount(sum);//add money to the cash register
			cout << "Collect your item at the bottom and enjoy.\n";
			cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
		}
		else cout << "The amount is not enough.Collect what you deposited.\n";
		
	}
}
void VendingMachine::sellProduct(const char nameJuice) {
	//choose juice to sell according to the name
	switch (nameJuice) {
		//send ref to the juice
	case orangeName:
		mannageSell(orange);
		break;
	case carrotName:
		mannageSell(carrot);
		break;
	case pomegranateName:
		mannageSell(pomegranate);
		break;
	}
}