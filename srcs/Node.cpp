/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:35:56 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/11 20:51:11 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Node.hpp"
#include <iostream>

using namespace	std;

Node::Node():_map(),
															_mapSize(0)
{
}

Node::Node(Node const &other):_map(),
															_mapSize(0)
{
	*this = other;
}

Node::~Node()
{
}

Node	&Node::operator=(Node const &other)
{
	if (this != &other)
	{
		//put here whatever make your object equal to an other
	}
	return *this;
}

Node::Node(vector<vector<Case *>> map, int mapSize):
															_map(map),
															_mapSize(mapSize),
															_costSoFar(0),
															_costToReach(0)
{}

Node::Node(vector<vector<Case *>> map, int mapSize, int costSoFar, Node *prev):
																				_map(map),
																				_mapSize(mapSize),
																				_costSoFar(costSoFar),
																				_costToReach(0),
																				_comeFrom(prev)

{
	(void)_comeFrom;
}

vector<vector<Case *>> const						Node::getMap() const
{
	return _map;
}

int													Node::getMapSize() const
{
	return _mapSize;
}

int													Node::getCostSoFar() const
{
	return _costSoFar;
}

int													Node::getCostToReach() const
{
	return _costToReach;
}

Case												*Node::getEmpty() const
{
	return _empty;
}
Node												*Node::getPrev() const
{
	return _comeFrom;
}

void												Node::setCostSoFar(int nc)
{
	_costSoFar = nc;
	return ;
}

void												Node::setCostToReach(int nc)
{
	_costToReach = nc;
	return ;
}

void												Node::setEmpty(Case *empty)
{
	_empty = empty;
}

bool												Node::operator<(Node const &other)
{
	int	totalO = other.getCostSoFar() + other.getCostToReach();
	int	totalT = this->_costSoFar + this->_costToReach;

	return totalT < totalO;
}

bool												Node::operator>(Node const &other)
{
	int	totalO = other.getCostSoFar() + other.getCostToReach();
	int	totalT = this->_costSoFar + this->_costToReach;

	return totalT > totalO;
}

bool												Node::operator==(Node const &other)
{
	for (int i = 0; i < _mapSize; i++)
	{
		for (int j = 0; j < _mapSize; j++)
		{
			if (*(other._map[i][j]) != *(_map[i][j]))
				return false;
		}
	}
	return true;
}

bool												Node::comp(Node *a, Node *b)
{
	return *a > *b;
}

std::ostream	&operator<<(std::ostream &o, Node const &c)
{
	(void)c;
	for (auto &it1: c.getMap())
	{
		for (auto &it2: it1)
			o << it2->getValue() << " ";
		o << std::endl;
	}
	return o;
}
