// Name:		Sean Pilon and Corey Crawford
// Professor:	Rigenberg
// Class:		CSCI 240
// Description:	We made a game that relates to shoots and ladders called Trap Doors and Trampolines. This program uses
// functions and nested functions to print the game header, get names, print the chart header, print the turns and caluclate how far
// the player moves with each turn keeping track of their last position and changing it when they have a new turn. Once a player reaches 
// a trap door or trampoline number it will send them to the corresponding number space. Once a player reaches the end number of 142
// the program wil stop and state what player has won the game.

#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>
#include <ctime>
#include <ostream>

using namespace std;

// all of the functions being declared
void printGameHeader();
void getName(string players[]);
void printChartHeader();
int printTurn(string, int, int);
int rollDice();
int movePlayer(int);
void printMove(int, string, int);
bool checkTraps(int&);
bool checkTrampolines(int&);
bool noWinner(int,string);


int main()
{
	int turn = 0;
	string players[3]; // array of where the players are being held
	int position[3][2]; // old position and new position are being held in the 2d array
	string special;
	string curPlayer;

	position[0][0] = 1; // setting all of the old positions to 1
	position[1][0] = 1;
	position[2][0] = 1;

	printGameHeader();
	getName(players);
	printChartHeader();
	while (noWinner(position[turn % 3][1],curPlayer))
	{

		curPlayer = players[turn % 3];
		printTurn(curPlayer, turn, position[turn % 3][0]);
		position[turn % 3][1] = movePlayer(position[turn % 3][0]);
		
		rollDice();
		
		if (checkTraps(position[turn % 3][1]))
		{
			special = "Trap!";
		}
		if (checkTrampolines(position[turn % 3][1]))
		{
			special = "Trampoline!";
		}

        printMove(rollDice(), special, position[turn % 3][1]);
		position[turn % 3][0] = position[turn % 3][1];
		turn++;
		if (turn % 3 == 0) {
			cout << "\n";
			printChartHeader();

		}
	}

	

}

void printGameHeader()
{

		cout << "+" << setfill('-') << setw(36) << "+" << endl;
		cout << "|" << setfill(' ') << setw(36) << "|" << endl;
		cout << "|" << setw(23) << "Welcome to" << setw(13) << "|" << endl;
		cout << "|" << setw(36) << "|" << endl;
		cout << "|" << setw(30) << "Trap Doors & Trampolines" << setw(6) << "|" << endl;
		cout << "+" << setfill('-') << setw(36) << "+" << endl;
		cout << "|" << setfill(' ') << setw(36) << "|" << endl;
		cout << "|" << setw(13) << "Trap Doors" << setw(20) << "Trampolines" << setw(3) << "|" << endl;
		cout << "|" << setw(13) << "----------" << setw(21) << "-------------" << setw(2) << "|" << endl;
		cout << "|" << setw(8) << "9" << setw(4) << "-> " << setw(3) << "2" << setw(9) << "3" << setw(7) << "-> " << " 59" << setw(2) << "|" << endl;
		cout << "|" << setw(8) << "22" << setw(4) << "-> " << setw(3) << "8" << setw(9) << "16" << setw(7) << "-> " << " 32" << setw(2) << "|" << endl;
		cout << "|" << setw(8) << "30" << setw(6) << " -> " " 14" << setw(9) << "33" << setw(7) << "-> " << " 54" << setw(2) << "|" << endl;
		cout << "|" << setw(8) << "51" << setw(6) << " -> " " 12" << setw(9) << "35" << setw(7) << "-> " << " 41" << setw(2) << "|" << endl;
		cout << "|" << setw(8) << "60" << setw(6) << " -> " " 42" << setw(9) << "56" << setw(7) << "-> " << " 78" << setw(2) << "|" << endl;
		cout << "|" << setw(8) << "88" << setw(6) << " -> " " 61" << setw(9) << "66" << setw(7) << "-> " << " 92" << setw(2) << "|" << endl;
		cout << "|" << setw(8) << "116" << setw(6) << " -> " " 86" << setw(9) << "96" << setw(7) << "-> " << "105" << setw(2) << "|" << endl;
		cout << "|" << setw(8) << "128" << setw(7) << "-> " "108" << setw(9) << "109" << setw(7) << "-> " << "140" << setw(2) << "|" << endl;
		cout << "|" << setw(8) << "135" << setw(7) << "-> " "100" << setw(9) << "124" << setw(7) << "-> " << "134" << setw(2) << "|" << endl;
		cout << "+" << setfill('-') << setw(36) << "+" << endl;
		cout << setfill(' ') << endl;
}
void getName(string players[])
{
	cout << "Enter Player 1 Name: " << endl;
	cin >> players[0];
	cout << "Enter Player 2 Name: " << endl;
	cin >> players[1];
	cout << "Enter Player 3 Name: " << endl;
	cin >> players[2];
}
void printChartHeader()
{

	cout << "Player" << setw(10) << "Turn" << setw(10) << "Old Pos" << setw(30) << "Dice" << setw(15) << "Special" << setw(10) << "New Pos" << endl;
	cout << setfill('-') << setw(85);
	cout << ' ' << endl;
	cout << setfill(' ');



}
int printTurn(string player, int turn, int oldPos)
{

	cout << setw(13) <<left<< player << right << setw(3) << turn << setw(10) << oldPos << setw(25) << "<Press enter to roll>" << setw(7);
	_getch();


	return oldPos;
}
int rollDice()
{
	srand((unsigned)time(0));
	int HIGH = 6;
	int LOW = 1;
	int dieOne = rand() % (HIGH - LOW + 1) + LOW;
	int dieTwo = rand() % (HIGH - LOW + 1) + LOW;

	int roll = dieOne + dieTwo;


	return roll;
}
int movePlayer(int oldPos)
{
	int newPos = oldPos + rollDice();

	checkTrampolines(newPos);
	checkTraps(newPos);

	return newPos;
}
bool checkTraps(int& position)
{

	bool trapHit = false;

	if (position == 9)
	{
		position = 2;
		return true;
	}
	else if (position == 22)
	{
		position = 8;
		trapHit = true;
	}
	else if (position == 30)
	{
		position = 14;
		trapHit = true;
	}
	else if (position == 51)
	{
		position = 12;
		trapHit = true;
	}
	else if (position == 60)
	{
		position = 42;
		trapHit = true;
	}
	else if (position == 88)
	{
		position = 61;
		trapHit = true;
	}
	else if (position == 116)
	{
		position = 86;
		trapHit = true;
	}
	else if (position == 135)
	{
		position = 100;
		trapHit = true;
	}
	return trapHit;
}
bool checkTrampolines(int& position)
{
	bool trampolineHit = false;
	if (position == 3)
	{
		position = 59;
		trampolineHit = true;
	}
	else if (position == 16)
	{
		position = 32;
		trampolineHit = true;
	}
	else if (position == 33)
	{
		position = 54;
		trampolineHit = true;
	}
	else if (position == 35)
	{
		position = 41;
		trampolineHit = true;
	}
	else if (position == 56)
	{
		position = 78;
		trampolineHit = true;
	}
	else if (position == 66)
	{
		position = 92;
		trampolineHit = true;
	}
	else if (position == 96)
	{
		position = 105;
		trampolineHit = true;
	}
	else if (position == 109)
	{
		position = 140;
		trampolineHit = true;
	}
	else if (position == 124)
	{
		position = 134;
		trampolineHit = true;
	}
	return trampolineHit;
}
bool noWinner(int pos, string winner)
{
	if (pos >= 142)
	{
		cout << winner << " Wins!";
		return false;
	}
	else return true;
}
void printMove(int dice, string special, int newPos)
{
	cout << dice << setw(10) << special << setw(10) << newPos << endl;
}