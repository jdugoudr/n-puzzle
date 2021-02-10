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

Puzzle::~Puzzle()
{
}

Puzzle::Puzzle(std::string heuristic_name):
	_numberOfStates(0),
	_numberOfMoves(0)
{
	_heuristic = createHeuristic(heuristic_name);
}

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



IHeuristic											*Puzzle::createHeuristic(std::string heuristic_name)
{
	typedef IHeuristic *(*func)();
	typedef struct {std::string name; func heuristic_func;} HeurCreateType;

	HeurCreateType			array[1] =
	{
		{"Manhattan", &createManhattanHeuristic}
	};

	IHeuristic		*ret;

	for (auto &it : array)
	{
		if (!it.name.compare(heuristic_name))
			ret = it.heuristic_func();
	}

	return (ret);
}

static IHeuristic									*createManhattanHeuristic()
{
	return (new Manhattan);
}
