#pragma once
#include <string>

using namespace std;

class Account {
private:
	string  name;
	double balance;

public:
	Account();
	void	setName(string s);
	string	getName();
	void	deposit(int a);
	void	withdraw(int a);
	double	getBalance();
	void	display();
};