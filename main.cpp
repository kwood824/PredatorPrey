#include <iostream>
#include "gameboard.h"

using std::cout;
using std::cin;
using std::endl;
using WoodGameBoard::GameBoard;

int main()
{
	GameBoard b(20, 20);
	b.createPlayBoard();
	b.createBoolBoard();
	try
	{
		b.initPlayBoard(100, 5);
	}
	catch (const int e)
	{
		cout << "Whoops!" << endl;
		cin.get();
	}
	b.printPlayBoard();
	cout << endl << "X = DoodleBug\tO = Ant" << endl << "Press ENTER to advance a step.";
	cin.get();

	while (1)
	{
		for (int i = 0; i < b.getRows(); i++)
		{
			for (int j = 0; j < b.getCols(); j++)
			{
				if (b.getBool(i, j) == false && b.getVal(i, j)->getSpecies() == 2)
				{
					b.getVal(i, j)->move(b.getPlayBoard(), b.getBoolBoard(), b.getRows(), b.getCols());
				}
			}
		}
		for (int i = 0; i < b.getRows(); i++)
		{
			for (int j = 0; j < b.getCols(); j++)
			{
				if (b.getBool(i, j) == false && b.getVal(i, j)->getSpecies() == 1)
				{
					b.getVal(i, j)->move(b.getPlayBoard(), b.getBoolBoard(), b.getRows(), b.getCols());
				}
			}
		}

		system("CLS");
		b.printPlayBoard();
		cout << endl << "X = DoodleBug\tO = Ant" << endl << "Press ENTER to advance a step.";
		b.resetBoolBoard();
		cin.get();
	}
	

	//cin.get();
	cin.get(); // I added these two to make the executable pause before closing when I compile at home

	return 0;
}