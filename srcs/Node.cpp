/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:35:56 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/12 16:31:26 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Node.hpp"

using namespace	std;

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

		for (int i = 0; i < _mapSize; i++)
		{
			std::vector<Case*>	tmp;
			for (int j = 0; j < _mapSize; j++)
			{
				Case	*newCase = new Case(*other._map[i][j]);
				tmp.push_back(newCase);
			}
			_map.push_back(tmp);
		}
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

void												Node::swap(size_t csrc, size_t lsrc,
																	size_t cdest, size_t ldest)
{
	std::swap(_map[csrc][lsrc], _map[cdest][ldest]);

	_map[csrc][lsrc]->setPosX(lsrc);
	_map[csrc][lsrc]->setPosY(csrc);
	_map[cdest][ldest]->setPosX(ldest);
	_map[cdest][ldest]->setPosY(cdest);

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
	int		width = 1;
	int		total_size = c.getMapSize() * c.getMapSize() - 1;

	while (total_size > 0)
	{
		total_size /= 10;
		width++;
	}

	for (auto &it1: c.getMap())
	{
		for (auto &it2: it1)
			o << setw(width) << it2->getValue();
		o << std::endl;
	}
	o << c.getCostSoFar() << " - " << c.getCostToReach() << std::endl;
	return o;
}
