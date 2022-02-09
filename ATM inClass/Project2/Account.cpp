#include "Account.h"
#include <string>
#include <iomanip>
#include <iostream>

using namespace std;

Account::Account() {
	name = "N/A";
	balance = 0;
}
void	Account::setName(string s)	 { name = s; }

string	Account::getName()			 { return name; }

double	Account::getBalance() { return balance; }

void	Account::deposit(int a)
{
	cout << "Please enter the amount [$0.01-$5,000.00]: " << endl;
	cin >> a;
	if (a >= 0.01 && a <= 5000) {
		balance = balance + a;
		cout << "Please enter in your next selection: " << endl;
	}
	else
	{
		cout << "The number that was entered is not a valid number." << endl;
		cout << "Please enter a valid number" << endl;
		cin >> a;
		balance = balance + a;
		cout << "Please enter your next selection: " << endl;
	}
}
void	Account::withdraw(int a)
{
	cout << "Please enter the amount in multiples of 10: ";
	cin >> a;
	if (a % 10 == 0 && a <= getBalance())
	{
		balance = balance - a;
		getBalance();
		cout << "Please enter in your next selection: " << endl;
	}
	else if (a < 0)
	{
		cout << "Amount not a positive number" << endl;
		cout << "Please enter a valid number: " << endl;
		cin >> a;
		balance = balance - a;
		getBalance();
		cout << "Please enter your next selection: " << endl;
	}
	else if (a % 10 != 0)
	{
		cout << "Amount is not a multiple of 10" << endl;
		cout << "Please enter a valid number: " << endl;
		cin >> a;
		balance = balance - a;
		getBalance();
		cout << "Please enter your next selection: " << endl;
	}
	else if (a > getBalance())
	{
		cout << "Insufficant Funds" << endl;
		cout << "Please enter a valid number" << endl;
		cin >> a;
		balance = balance - a;
		getBalance();
		cout << "Please enter your next selection: " << endl;
	}


}



void  Account::display()
{
	cout << getName() << " :  $" << getBalance() << setprecision(2) << fixed << endl;
	cout << "Please enter your next selection: " << endl;
}



