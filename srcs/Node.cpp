/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:35:56 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/17 17:45:22 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Node.hpp"
#include "AStar.hpp"
#include <limits.h>

Node::Node():_map(),
						_mapSize(0)
{
}

Node::Node(Node const &other):_map(),
															_mapSize(other._mapSize)
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
		_costSoFar = other._costSoFar;
		_costToReach = INT_MAX;
		_comeFrom = other._comeFrom;
		_map = other._map;
	}
	return *this;
}

Node::Node(std::vector<int> map, int mapSize):
															_map(),
															_mapSize(mapSize),
															_costSoFar(0),
															_costToReach(0)
{
	_map._map = map;
}

Node::Node(std::vector<int> map, int mapSize, int costSoFar, Node *prev):
																				_map(),
																				_mapSize(mapSize),
																				_costSoFar(costSoFar),
																				_costToReach(0),
																				_comeFrom(prev)

{
	_map._map = map;
}

Node::Node(Map	 map, int mapSize, int costSoFar, Node *prev):
																				_map(),
																				_mapSize(mapSize),
																				_costSoFar(costSoFar),
																				_costToReach(0),
																				_comeFrom(prev)

{
	_map._map = map._map;
	_map._empty = map._empty;
}

std::vector<int> const						Node::getMap() const
{
	return _map._map;
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

int													Node::getEmpty() const
{
	return _map._empty;
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

void												Node::setEmpty(int empty)
{
	_map._empty = empty;
	return ;
}

void												Node::setComeFrom(Node *p)
{
	_comeFrom = p;
	return ;
}

void												Node::swap(size_t src, size_t dest)
{
	std::swap(_map._map[src], _map._map[dest]);
	return ;
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
	return _map._map == other._map._map;
}

bool												Node::comp(Node *a, Node *b)
{
	return *a > *b;
}

bool 					Node::find_in_queue(Node *el, Node *toFind)
{
	return *el == *toFind;
}

std::ostream	&operator<<(std::ostream &o, Node const &c)
{
	int		width = 1;
	int		size = c.getMapSize();
	int		total_size = size * size - 1;

	while (total_size > 0)
	{
		total_size /= 10;
		width++;
	}

	int	i = 0;
	for (auto &it1: c.getMap())
	{
		o << std::setw(width) << it1;
		i++;
		if (i % size == 0)
			o << std::endl;
	}
	o <<std::setw(width) <<  c.getCostSoFar() << " - " << c.getCostToReach() << std::endl;
	return o;
}

std::ostream	&operator<<(std::ostream &o, Map const &c)
{
	int		width = 1;
	int		size = AStar::getSize();
	int		total_size = size * size - 1;

	while (total_size > 0)
	{
		total_size /= 10;
		width++;
	}

	int	i = 0;
	for (auto &it1: c._map)
	{
		o << std::setw(width) << it1;
		i++;
		if (i % size == 0)
			o << std::endl;
	}
	o <<std::setw(width) <<  c._gscore << " - " << c._fscore - c._gscore << std::endl;
	return o;
}

std::ostream	&operator<<(std::ostream &o, PairMap const &c)
{
	int		width = 1;
	int		size = AStar::getSize();
	int		total_size = size * size - 1;

	while (total_size > 0)
	{
		total_size /= 10;
		width++;
	}

	int	i = 0;
	for (auto &it1: c._map)
	{
		o << std::setw(width) << it1;
		i++;
		if (i % size == 0)
			o << std::endl;
	}
	return o;
}
