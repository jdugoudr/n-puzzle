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

Puzzle::~Puzzle()
{
}

Puzzle::Puzzle(IHeuristic *heuristic):
	_heuristic(heuristic),
	_numberOfStates(0),
	_numberOfMoves(0)
{
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

list<Node *>										Puzzle::getOpenList() const
{
	return _openList;
}

list<Node *>										Puzzle::getClosedList() const
{
	return _closedList;
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

void												Puzzle::setOpenList(list<Node *> open_list)
{
	_openList = open_list;
}

void												Puzzle::setClosedList(list<Node *> closed_list)
{
	_closedList = closed_list;
}

void												Puzzle::setNumberOfStates(int nb)
{
	_numberOfStates = nb;
}

void												Puzzle::setNumberOfMoves(int nb)
{
	_numberOfMoves = nb;
}
