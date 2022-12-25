/* Assignment C++: 1
Author: Yuval Hendler, ID: 324180363
Author: Ori Sadek, ID: 211973011
*/
#include "CashRegister.h"

CashRegister::CashRegister(int cashNum) { //Constructor
	cashOnHands = cashNum;
}

CashRegister::~CashRegister() {}; //Destructor

int CashRegister::getCurrentBalance() const { //get the cash value
	return cashOnHands;
}

void CashRegister::acceptAmount(int payedMoney) {
	cashOnHands = payedMoney + cashOnHands; //add money to register
}



