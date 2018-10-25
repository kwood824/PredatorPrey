#include "organism.h"

namespace WoodOrganism
{
	//	Organism Class
	Organism::Organism()	:species(unknown)
	{
		/*Intentionally empty*/
	}
	Organism::Organism(int newRow, int newCol)	:species(unknown)
	{
		rowPos = newRow;
		ColPos = newCol;
	}
	void Organism::setRow(const int & newPos)
	{
		rowPos = newPos;
	}
	void Organism::setCol(const int & newPos)
	{
		ColPos = newPos;
	}
	void Organism::setSpecies(const speciesType & newSpecies)
	{
		species = newSpecies;
	}
	void Organism::setMoveRow(const int & newPos)
	{
		moveRow = newPos;
	}
	void Organism::setMoveCol(const int & newPos)
	{
		moveCol = newPos;
	}
	int Organism::getRow() const
	{
		return rowPos;
	}
	int Organism::getCol() const
	{
		return ColPos;
	}
	speciesType Organism::getSpecies() const
	{
		return species;
	}
	int Organism::getMoveRow() const
	{
		return moveRow;
	}
	int Organism::getMoveCol() const
	{
		return moveCol;
	}
	void Organism::move(vector<vector<shared_ptr<Organism>>>& playBoard, vector<vector<bool>>& boolBoard, const int& rows, const int& cols)
	{
		boolBoard[getRow()][getCol()] = true;
	}
	bool Organism::getDirection(vector<vector<shared_ptr<Organism>>>& playBoard, const int & rows, const int & cols, const speciesType & target)
	{
		setMoveRow(getRow());		//Setting move targets to organism's current position
		setMoveCol(getCol());

		vector<int> choices {1, 2, 3, 4};
		
		for (int i = 0; i < 4; i++)
		{
			int direction = (rand() % choices.size());

			switch (choices[direction])
			{
			case 1:		//Move up
				if (getRow() - 1 >= 0 && playBoard[getRow() - 1][getCol()]->getSpecies() == target)
				{
					setMoveRow(getRow() - 1);
					return true;
				}
				break;
			case 2:		//Move down
				if (getRow() + 1 < rows && playBoard[getRow() + 1][getCol()]->getSpecies() == target)
				{
					setMoveRow(getRow() + 1);
					return true;
				}
				break;
			case 3:		//Move left
				if (getCol() - 1 >= 0 && playBoard[getRow()][getCol() - 1]->getSpecies() == target)
				{
					setMoveCol(getCol() - 1);
					return true;
				}
				break;
			case 4:		//Move right
				if (getCol() + 1 < cols && playBoard[getRow()][getCol() + 1]->getSpecies() == target)
				{
					setMoveCol(getCol() + 1);
					return true;
				}
				break;
			default:
				break;
			}

			choices.erase(choices.begin() + direction);
		}

		return false;
	}
	void Organism::changePosition(vector<vector<shared_ptr<Organism>>>& playBoard, vector<vector<bool>>& boolBoard)
	{
		playBoard[getMoveRow()][getMoveCol()] = playBoard[getRow()][getCol()];		//copy Organism data to new location
		playBoard[getRow()][getCol()] = (make_shared<Organism>(getRow(), getCol()));	//put a blank Organism in the location moved from
		boolBoard[getMoveRow()][getMoveCol()] = true;		//set the moved to location to true so it doesn't move twice
		boolBoard[getRow()][getCol()] = true;				//set the moved from location to true
		setRow(getMoveRow());			//set Organism's row data to its new location
		setCol(getMoveCol());			//set Organism's column data to its new location
	}
	Organism::~Organism()
	{
		/*Intentionally empty*/
	}
	//	!Organism Class

	/******************************************************************************************/

	//	Ant Class
	Ant::Ant()	:Organism(), breedCount(0)
	{
		setSpecies(ant);
	}
	Ant::Ant(int newRow, int newCol)	:Organism(newRow, newCol), breedCount(0)
	{
		setSpecies(ant);
	}
	void Ant::move(vector<vector<shared_ptr<Organism>>>& playBoard, vector<vector<bool>>& boolBoard, const int& rows, const int& cols)
	{
		speciesType target = unknown;

		if (getDirection(playBoard, rows, cols, target))
		{
			changePosition(playBoard, boolBoard);
		}

		breedCount++;
		if (breedCount >= 3)
		{
			breed(playBoard, boolBoard, rows, cols);
		}
	}
	Ant::~Ant()
	{
		/*Intentionally empty*/
	}
	void Ant::breed(vector<vector<shared_ptr<Organism>>>& playBoard, vector<vector<bool>>& boolBoard, const int & rows, const int & cols)
	{
		speciesType target = unknown;

		if (getDirection(playBoard, rows, cols, target))
		{
			playBoard[getMoveRow()][getMoveCol()] = (make_shared<Ant>(getMoveRow(), getMoveCol()));
			boolBoard[getMoveRow()][getMoveCol()] = true;
		}
		
		breedCount = 0;
	}
	//	!Ant Class

	/******************************************************************************************/

	//	DoodleBug Class
	DoodleBug::DoodleBug()	:Organism(), breedCount(0), deathCount(0)
	{
		setSpecies(doodlebug);
	}

	DoodleBug::DoodleBug(int newRow, int newCol)	:Organism(newRow, newCol), breedCount(0), deathCount(0)
	{
		setSpecies(doodlebug);
	}
	void DoodleBug::move(vector<vector<shared_ptr<Organism>>>& playBoard, vector<vector<bool>>& boolBoard, const int & rows, const int & cols)
	{
		if (!eat(playBoard, boolBoard, rows, cols))
		{
			speciesType target = unknown;

			if (getDirection(playBoard, rows, cols, target))
			{
				changePosition(playBoard, boolBoard);
			}

			deathCount++;	//Starving!
		}

		breedCount++;
		if (breedCount >= 8)
		{
			breed(playBoard, boolBoard, rows, cols);
		}

		if (deathCount >= 3)
		{
			die(playBoard);
		}
	}
	DoodleBug::~DoodleBug()
	{
		/*Intentionally empty*/
	}
	bool DoodleBug::eat(vector<vector<shared_ptr<Organism>>>& playBoard, vector<vector<bool>>& boolBoard, const int & rows, const int & cols)
	{
		speciesType target = ant;

		if (getDirection(playBoard, rows, cols, target))
		{
			changePosition(playBoard, boolBoard);
			return true;
		}

		return false;
	}
	void DoodleBug::breed(vector<vector<shared_ptr<Organism>>>& playBoard, vector<vector<bool>>& boolBoard, const int & rows, const int & cols)
	{
		speciesType target = unknown;

		if (getDirection(playBoard, rows, cols, target))
		{
			playBoard[getMoveRow()][getMoveCol()] = (make_shared<DoodleBug>(getMoveRow(), getMoveCol()));
			boolBoard[getMoveRow()][getMoveCol()] = true;
		}

		breedCount = 0;
	}
	void DoodleBug::die(vector<vector<shared_ptr<Organism>>>& playBoard)
	{
		playBoard[getRow()][getCol()] = (make_shared<Organism>(getRow(), getCol()));
	}
	//	!DoodleBug Class
}