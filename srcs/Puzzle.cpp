/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Puzzle.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:35:56 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/08 22:09:44 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Puzzle.hpp"
#include <iostream>

using namespace	std;

static IHeuristic		*createManhattanHeuristic();

Puzzle::Puzzle():
	_numberOfStates(0),
	_numberOfMoves(0),
	_solvabilityCheck(1),
	_mustBeSolvable(1)
{
}

Puzzle::~Puzzle()
{
}

/*Puzzle::Puzzle(std::string heuristic_name):
	_numberOfStates(0),
	_numberOfMoves(0)
{
	_heuristic = createHeuristic(heuristic_name);
}*/

IHeuristic const									*Puzzle::getHeuristic() const
{
	return _heuristic;
}

Node const											*Puzzle::getStartNode() const
{
	return _startNode;
}

Node const											*Puzzle::getEndNode() const
{
	return _endNode;
}

int													Puzzle::getMapSize() const
{
	return _mapSize;
}

int													Puzzle::getNumberOfStates() const
{
	return _numberOfStates;
}

int													Puzzle::getNumberOfMoves() const
{
	return _numberOfMoves;
}

std::string											Puzzle::getFilename() const
{
	return _filename;
}

bool												Puzzle::getSolvabilityCheck() const
{
	return _solvabilityCheck;
}

bool												Puzzle::getMustBeSolvable() const
{
	return _mustBeSolvable;
}






static IHeuristic									*createManhattanHeuristic()
{
	return (new Manhattan);
}

void												Puzzle::setHeuristic(std::string heuristic_name)
{
	typedef IHeuristic *(*func)();
	typedef struct {std::string name; func heuristic_func;} HeurCreateType;

	HeurCreateType			array[1] =
	{
		{"Manhattan", &createManhattanHeuristic}
	};

	for (auto &it: array)
	{
		if (!it.name.compare(heuristic_name))
			_heuristic = it.heuristic_func();
	}
}

void												Puzzle::setStartNode(Node *node)
{
	_startNode = node;
}

void												Puzzle::setEndNode(Node *node)
{
	_endNode = node;
}

void												Puzzle::setMapSize(int size)
{
	_mapSize = size;
}

void												Puzzle::setNumberOfStates(int nb)
{
	_numberOfStates = nb;
}

void												Puzzle::setNumberOfMoves(int nb)
{
	_numberOfMoves = nb;
}

void												Puzzle::setFilename(std::string filename)
{
	_filename = filename;
}

void												Puzzle::setSolvabilityCheck(bool state)
{
	_solvabilityCheck = state;
}

void												Puzzle::setMustBeSolvable(bool state)
{
	_mustBeSolvable = state;
}





int													Puzzle::countInversions(std::vector<int> const &map, int size) const
{
	int		inversions = 0;

	for (int i = 0; i < (size * size - 1); i++)
	{
		for (int j = i + 1; j < (size * size); j++)
		{
			if (map[i] && map[j] && map[i] > map[j])
				inversions++;
		}
	}

	return (inversions);
}

bool												Puzzle::isSolvable(void) const
{
	if (!this->_startNode || !this->_endNode)
		return (0);

	int start_inversions = countInversions(this->_startNode->getMap(), this->_mapSize);
	int end_inversions = countInversions(this->_endNode->getMap(), this->_mapSize);

	if (this->_mapSize % 2 == 0)
	{
		start_inversions += (this->_startNode->getEmpty() / this->_mapSize);
		end_inversions += (this->_endNode->getEmpty() / this->_mapSize);
	}

	return (start_inversions % 2 == end_inversions % 2);
}
