#pragma once

#ifndef ORGANISM_H
#define ORGANISM_H

#include <string>
#include <vector>
#include <memory>

using std::string;
using std::vector;
using std::shared_ptr;
using std::make_shared;

namespace WoodOrganism
{
	enum speciesType { unknown = 0, ant = 1, doodlebug = 2 };

	class Organism
	{
	public:
		Organism();
		Organism(int newRow, int newCol);
		void setRow(const int& newPos);
		void setCol(const int& newPos);
		void setSpecies(const speciesType& newSpecies);
		void setMoveRow(const int& newPos);
		void setMoveCol(const int& newPos);
		int getRow() const;
		int getCol() const;
		speciesType getSpecies() const;
		int getMoveRow() const;
		int getMoveCol() const;
		virtual void move(vector<vector<shared_ptr<Organism>>>& playBoard, vector<vector<bool>>& boolBoard, const int& rows, const int& cols);
		virtual ~Organism();
	protected:
		bool getDirection(vector<vector<shared_ptr<Organism>>>& playBoard, const int& rows, const int& cols, const speciesType& target);
		void changePosition(vector<vector<shared_ptr<Organism>>>& playBoard, vector<vector<bool>>& boolBoard);
	private:
		int rowPos, ColPos, moveRow, moveCol;
		speciesType species;
	};

	class Ant : public Organism
	{
	public:
		Ant();
		Ant(int newRow, int newCol);
		virtual void move(vector<vector<shared_ptr<Organism>>>& playBoard, vector<vector<bool>>& boolBoard, const int& rows, const int& cols);
		virtual ~Ant();
	private:
		int breedCount;
		void breed(vector<vector<shared_ptr<Organism>>>& playBoard, vector<vector<bool>>& boolBoard, const int& rows, const int& cols);
	};

	class DoodleBug : public Organism
	{
	public:
		DoodleBug();
		DoodleBug(int newRow, int newCol);
		virtual void move(vector<vector<shared_ptr<Organism>>>& playBoard, vector<vector<bool>>& boolBoard, const int& rows, const int& cols);
		virtual ~DoodleBug();
	private:
		int breedCount, deathCount;
		bool eat(vector<vector<shared_ptr<Organism>>>& playBoard, vector<vector<bool>>& boolBoard, const int& rows, const int& cols);
		void breed(vector<vector<shared_ptr<Organism>>>& playBoard, vector<vector<bool>>& boolBoard, const int& rows, const int& cols);
		void die(vector<vector<shared_ptr<Organism>>>& playBoard);
	};

}

#endif // !ORGANISM_H
