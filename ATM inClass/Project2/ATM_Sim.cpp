#include <iostream>
#include <iomanip>
#include <string>
#include "Account.h"
using namespace std;

// prototypes
int  getSelection();
void printMenu();

int main() {
	Account myAcct;

	int amount = 0;
	int	selection;
	
	myAcct.setName("Bruce Wayne");
	

	cout << setw(7) << "Hello " << myAcct.getName();
	cout << endl;
	

	printMenu();				   

	selection = getSelection();   //You need to implement this function below

	while (selection != 4) {
		if (selection == 1) {
				myAcct.deposit(amount);

		}

		else if (selection == 2) {
			myAcct.withdraw(amount);
		}

		else if (selection == 3) {
			myAcct.display();
		}
		else if (selection != 4) {
			cout << "Please enter in a valid number choice" << endl;
		}


		selection = getSelection();  //You need to implement this function below
	}
	

	cout << "Goodbye!" << endl;
	return 0;
}

void printMenu()
{
	cout << setw(18) << setfill('*')  << "Oiler Banking" <<  setfill('*') << endl;
	cout << setfill(' ') << endl;

	cout << setw(14) << "[1] Deposit" << endl;
	cout << setw(15) << "[2] Withdraw" << endl;
	cout << setw(14) << "[3] Balance" << endl;
	cout << setw(11) << "[4] Done" << endl;
	cout << setw(55) << setfill('*') << endl;

	cout << "\nPlease enter in your selection: " << endl;
}
int getSelection()
{
	int selection;

	cin >> selection;

	return selection;
}
