/* Assignment C++: 1
Author: Yuval Hendler, ID: 324180363
Author: Ori Sadek, ID: 211973011
*/
class DispenserType {
	int numberOfItems;
	int cost;
public:
	DispenserType(); //Constructor
	DispenserType(int numberOfItems, int cost); //Constructor
	~DispenserType(); //Destructor
	int getNoOfItems() const;
	int getCost() const;
	void makeSale();

};