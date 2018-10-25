#pragma once

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include <memory>
#include "organism.h"

using std::vector;
using std::shared_ptr;
using std::make_shared;
using WoodOrganism::Organism;
using WoodOrganism::Ant;
using WoodOrganism::DoodleBug;

typedef shared_ptr<Organism> OrganismPtr;

namespace WoodGameBoard
{
	class GameBoard
	{
	public:
		GameBoard();
		GameBoard(int numRows, int numCols);
		void setRows(const int& newRows);
		void setCols(const int& newCols);
		int getRows() const;
		int getCols() const;
		OrganismPtr getVal(const int& rowPos, const int& colPos) const;
		bool getBool(const int& rowPos, const int& colPos) const;
		vector<vector<OrganismPtr>>& getPlayBoard();
		vector<vector<bool>>& getBoolBoard();
		void createPlayBoard();
		void initPlayBoard(int numAnts, int numDoodle);
		void printPlayBoard();
		void createBoolBoard();
		void resetBoolBoard();
		void setAnt(const int& rowPos, const int& colPos);
		void setDoodle(const int& rowPos, const int& colPos);
		void setTrue(const int& rowPos, const int& colPos);
		void setFalse(const int& rowPos, const int& colPos);
		~GameBoard();
	private:
		int rows, cols;
		vector<vector<OrganismPtr>> playBoard;
		vector<vector<bool>> boolBoard;
	};
}

#endif // !GAMEBOARD_H
