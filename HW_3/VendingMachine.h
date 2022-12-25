/* Assignment C++: 1
Author: Yuval Hendler, ID: 324180363
Author: Ori Sadek, ID: 211973011
*/
#include "DispenserType.h"
#include "CashRegister.h"

class VendingMachine {
	DispenserType orange;
	DispenserType carrot;
	DispenserType pomegranate;
	CashRegister counter;
	void mannageSell(DispenserType& juiceType); //manage the sell
public:
	//names of the juices
	const static char orangeName = 'o';
	const static char carrotName = 'c';
	const static char pomegranateName = 'p';
	VendingMachine(); // Constructor
	void sellProduct(const char nameJuice); //sell the juice
	~VendingMachine(); //Destructor

};