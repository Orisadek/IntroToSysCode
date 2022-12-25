/* Assignment C++: 1
Author: Yuval Hendler, ID: 324180363
Author: Ori Sadek, ID: 211973011
*/

class Menu {
	int showJuiceMenu() const; //take the input of the choosen juice
	int showStackMenu() const;
public:
	~Menu(); //Destructor
	Menu(); //Constructor
	int mainMenu() const; //regular menu
	int shopMenu() const; //shop menu
	int stackMenu() const;  //stack menu
};