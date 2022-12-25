/* Assignment C++: 1
Author: Yuval Hendler, ID: 324180363
Author: Ori Sadek, ID: 211973011
*/

#include "Menu.h"
#include "VendingMachine.h"
#include "Stack.h"
#include <iostream>

/*#define ORANGE 'o'
#define CARROT 'c'
#define POMEGRANTE 'p'*/

#define INVALID "Invalid Selection.\n"
#define THANKS "Thank you!\n"

using namespace std;
Menu::Menu() {}
Menu::~Menu() {};

int Menu::mainMenu() const {
	int fl = 1;
	while (fl) {
		int input;
		//print menu
		cout << "(1) Fresh juice Shop\n";
		cout << "(2) Integer Stack\n";
		cout << "(3) Exit\n";
		cin >> input;
		//choose option
		switch (input) {
		case 1:
			shopMenu();
			break;
		case 2:
			stackMenu();
			break;
		case 3:
			fl = 0; //get out of while loop
			break;
		default:
			cout << INVALID;
		}
	}
	cout << "Goodbye!\n";
	return 0;
}

int Menu::showStackMenu() const {
	int input;
	cout << "*** Manage your integer stack ***\n";
	cout << "1 Push new element\n";
	cout << "2 Pop element\n";
	cout << "3 Show the first element\n";
	cout << "4 Check if empty\n";
	cout << "5 to exit\n";
	cin >> input;
	return input;
}

int Menu::showJuiceMenu() const {
	//print menu
	int input;
	cout << "*** Welcome to juice Shop ***\n";
	cout << "To select an item, enter\n";
	cout << "1 For Orange juice\n";
	cout << "2 For Carrot juice\n";
	cout << "3 For Pomegranate\n";
	cout << "4 To exit\n";
	cin >> input;
	return input;
}

int Menu::shopMenu() const {
	bool fl = true;
	VendingMachine vendingMachine;
	while (fl) {
		//get the input
		int input = showJuiceMenu();
		switch (input) { //choose juice
		case 1:
			vendingMachine.sellProduct(VendingMachine::orangeName);
			break;
		case 2:
			vendingMachine.sellProduct(VendingMachine::carrotName);
			break;
		case 3:
			vendingMachine.sellProduct(VendingMachine::pomegranateName);
			break;
		case 4:
			fl = false; //get out of the while loop of juice Menu
			break;
		default:
			cout << INVALID;
		}
	}
	cout << THANKS;
	return 0;
}

int Menu::stackMenu() const {
	bool fl = true;
	Stack* stack = new Stack;
	while (fl) {
		int input = showStackMenu();
		switch (input) {
		case 1:
			stack->mannagePush();
			break;
		case 2:
			stack->pop();
			break;
		case 3:
			cout << "The first element is:" << stack->peek() << endl;
			break;
		case 4:
			if (stack->isEmpty())cout << "The stack is empty\n";
			else cout << "The stack is not empty\n";
			break;
		case 5:
			fl = false;
			break;
		default:
			cout << INVALID;
		}
	}
	cout << THANKS;
	delete stack;
	return 0;
}
