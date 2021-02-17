/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:35:56 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/12 22:36:32 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Node.hpp"

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
		_costToReach = other._costToReach;
		_comeFrom = other._comeFrom;
		_map = other._map;
	}
	return *this;
}

Node::Node(std::vector<int> map, int mapSize):
															_map(map),
															_mapSize(mapSize),
															_costSoFar(0),
															_costToReach(0)
{
}

Node::Node(std::vector<int> map, int mapSize, int costSoFar, Node *prev):
																				_map(map),
																				_mapSize(mapSize),
																				_costSoFar(costSoFar),
																				_costToReach(0),
																				_comeFrom(prev)

{
}

std::vector<int> const								&Node::getMap() const
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

int													Node::getEmpty() const
{
	for (int pos = 0 ; pos < _mapSize * _mapSize ; pos++)
		if (_map[pos] == 0)
			return pos;
	throw std::out_of_range("Out of Range while looking for neighbor ");
	return 0;
	//return _empty;
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
	_empty = empty;
	return ;
}

void												Node::setComeFrom(Node *p)
{
	_comeFrom = p;
	return ;
}

void												Node::swap(size_t src, size_t dest)
{
	std::swap(_map[src], _map[dest]);
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
	return _map == other._map;
}

bool												Node::comp(Node *a, Node *b)
{
	return *a > *b;
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
