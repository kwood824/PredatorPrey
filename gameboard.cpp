#include <vector>
#include <time.h>
#include <iostream>
#include "gameboard.h"

using std::vector;
using std::cout;
using std::endl;
using std::fill;

typedef shared_ptr<Organism> OrganismPtr;

namespace WoodGameBoard
{
	GameBoard::GameBoard()	:rows(20), cols(20)
	{
		srand(time(NULL));
	}
	GameBoard::GameBoard(int numRows, int numCols)	:rows(numRows), cols(numCols)
	{
		srand(time(NULL));
	}
	void GameBoard::setRows(const int & newRows)
	{
		rows = newRows;
	}
	void GameBoard::setCols(const int & newCols)
	{
		cols = newCols;
	}
	int GameBoard::getRows() const
	{
		return rows;
	}
	int GameBoard::getCols() const
	{
		return cols;
	}
	OrganismPtr GameBoard::getVal(const int & rowPos, const int & colPos) const
	{
		return playBoard[rowPos][colPos];
	}
	bool GameBoard::getBool(const int & rowPos, const int & colPos) const
	{
		return boolBoard[rowPos][colPos];
	}
	vector<vector<OrganismPtr>>& GameBoard::getPlayBoard()
	{
		return playBoard;
	}
	vector<vector<bool>>& GameBoard::getBoolBoard()
	{
		return boolBoard;
	}
	void GameBoard::createPlayBoard()
	{
		playBoard.resize(rows);
		fill(playBoard.begin(), playBoard.end(), vector<OrganismPtr>(cols, make_shared<Organism>()));
	}
	void GameBoard::initPlayBoard(int numAnts, int numDoodle)
	{
		if (numAnts + numDoodle > getRows() * getCols())
		{
			cout << "ERROR: Too many bugs for the board space!" << endl;
			throw 0;
		}

		int count = 0;
		while (count < numAnts)
		{
			int testRow = rand() % getRows();
			int testCol = rand() % getCols();

			if (playBoard[testRow][testCol]->getSpecies() == 0)
			{
				setAnt(testRow, testCol);
				count++;
			}
		}

		count = 0;
		while (count < numDoodle)
		{
			int testRow = rand() % getRows();
			int testCol = rand() % getCols();

			if (playBoard[testRow][testCol]->getSpecies() == 0)
			{
				setDoodle(testRow, testCol);
				count++;
			}
		}
	}
	void GameBoard::printPlayBoard()
	{
		int a = 0, b = 0;

		for (vector<vector<OrganismPtr>>::iterator i = playBoard.begin(); i < playBoard.end(); ++i)
		{
			for (vector<OrganismPtr>::iterator j = i->begin(); j < i->end(); ++j)
			{
				//cout << playBoard[a][b]->getSpecies() << "\t";
				if (playBoard[a][b]->getSpecies() == 1)
				{
					cout << "O\t";
				}
				else if (playBoard[a][b]->getSpecies() == 2)
				{
					cout << "X\t";
				}
				else
				{
					cout << ".\t";
				}
				++b;
			}
			b = 0;
			cout << endl;
			++a;
		}
	}
	void GameBoard::createBoolBoard()
	{
		boolBoard.resize(rows);
		fill(boolBoard.begin(), boolBoard.end(), vector<bool>(cols, false));
	}
	void GameBoard::resetBoolBoard()
	{
		fill(boolBoard.begin(), boolBoard.end(), vector<bool>(cols, false));
	}
	void GameBoard::setAnt(const int & rowPos, const int & colPos)
	{
		playBoard[rowPos][colPos] = (make_shared<Ant>(rowPos, colPos));
	}
	void GameBoard::setDoodle(const int & rowPos, const int & colPos)
	{
		playBoard[rowPos][colPos] = (make_shared<DoodleBug>(rowPos, colPos));
	}
	void GameBoard::setTrue(const int & rowPos, const int & colPos)
	{
		boolBoard[rowPos][colPos] = true;
	}
	void GameBoard::setFalse(const int & rowPos, const int & colPos)
	{
		boolBoard[rowPos][colPos] = false;
	}
	GameBoard::~GameBoard()
	{
		playBoard.clear();
		boolBoard.clear();
	}
}