/* Assignment C++: 1
Author: Yuval Hendler, ID: 324180363
Author: Ori Sadek, ID: 211973011
*/

class CashRegister {
	int cashOnHands;
public:
	~CashRegister(); // Destructor
	CashRegister(int cashNum = 0); // Constructor
	int getCurrentBalance() const;
	void acceptAmount(int payedMoney);
};