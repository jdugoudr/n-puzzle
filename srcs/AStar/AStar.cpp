/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AStar.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 17:20:50 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/17 22:38:30 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AStar.hpp"
//#include "find_if_mix.hpp"
#include <algorithm>
#include <iostream>

AStar::~AStar()
{
//	std::for_each(_closedList.begin(), _closedList.end(), AStar::erase_pair);
//	std::for_each(_openList.begin(), _openList.end(), AStar::erase);
//	_closedSet.clear();
//	_openSet.clear();
	while (!_openList.empty())
		_openList.pop();
}

AStar::AStar(Node *start, Node const &goal, IHeuristic const &h):
																				_goal(goal),
																				_h(h),
																				_start(start),
																				_curr(),
																				_set(),
	//																			_closedSet(),
	//																			_openSet(),
																				_openList(Map::comp)
{
	AStar::_size = start->getMapSize();
}

std::vector<int>		AStar::swapMap(int src, int dest, std::vector<int> map)
{
	std::vector<int>	newMap = map;
	
	std::swap(newMap[src], newMap[dest]);

	return newMap;	
}

void display_open(std::pair<std::vector<int>, Map*> const &el)
{
	Map	const &m = *std::get<1>(el);

	if (m._isOpen)
		std::cout << m << std::endl;
}
void display_close(std::pair<std::vector<int>, Map*> const &el)
{
	Map	const &m = *std::get<1>(el);

	if (!m._isOpen)
		std::cout << m << std::endl;
}

void							AStar::run()
{
	_start->setCostToReach(_h.calculate(_start->getMap(), _goal));
	Map start(_start->getMap(),
				nullptr, 0, _start->getCostToReach(),
				_start->getEmpty());

	_openList.push(&start);
	_set.insert(std::make_pair(start._map, &start));//Attention il doit etre malloc, gare au invalid free !!

	while (!_openList.empty())
	{
		_curr = *_openList.top();
		if(_curr._map == _goal.getMap())
		{
			std::cout << *_set[_curr._map];
			return ;
		}

		pushFromOpenToClose(_curr);//pop priority_queue

		int	tentative_g = _curr._gscore + 1;
		for (auto it: getNeighbor(_curr))
		{
			auto el = _set.find(it._map);
			if ( el != _set.end())
			{
				Map	&oldNode = *(std::get<1>(*el));
				if (oldNode._gscore > tentative_g)
				{
					oldNode._parent = &_curr;
					oldNode._fscore = oldNode._gscore - (oldNode._gscore - tentative_g);
					oldNode._gscore = tentative_g;
					if (!oldNode._isOpen)
					{
						pushFromCloseToOpen(oldNode);
					}
				//	else
				//	{
				//		_openList.re_push(oldNode._pair);
				//	}
				}
				else
					continue ;
			}
			else
			{
				pushNewNodeToOpen(tentative_g, _h.calculate(it._map, _goal), it, _curr);
			}
		}
//		debug();
	}
	throw AStar::NoSolution();
	return ;
}

void							AStar::pushNewNodeToOpen(int soFar, int toReach, Map &map, Map &parent)
{
	try {
		Map	&ref = *(new Map(map, parent));
	//	_set[map._map] = Map(map, parent);

	//	Map	&ref = *_set[map._map];

		ref._gscore = soFar;
		ref._fscore = soFar + toReach;

		_openList.push(&ref);
		ref._isOpen = true;

		_set[map._map] = &ref;


	} catch (std::exception &e) {
		throw e;
	}
	return ;
}

void							AStar::pushOpenList(Map &node)
{
	(void)node;
	return ;
}

void							AStar::pushFromOpenToClose(Map &m)
{
	m._isOpen = false;
	_openList.pop();
	return ;
}

void							AStar::pushFromCloseToOpen(Map &n)
{
	n._isOpen = true;
	_openList.push(&n);
	return ;
}

std::vector<Map>			AStar::getNeighbor(Map &m)
{
	std::vector<Map>		lst;
	Map									str_map;
	std::vector<int>		curr_map = m._map;

	int posZero = m._empty;
	int i = posZero / _size;
	int j = posZero % _size;

	//Move to right
	if (j + 1 < _size)
	{
		str_map._map = swapMap(posZero, posZero + 1, curr_map);
		str_map._empty = posZero + 1;
		lst.push_back(str_map);
	}
	//Move to left
	if (j > 0)
	{
		str_map._map = swapMap(posZero, posZero - 1, curr_map);
		str_map._empty = posZero - 1;
		lst.push_back(str_map);
	}
	//Move down
	if (i > 0)
	{
		str_map._map = swapMap(posZero, posZero - _size, curr_map);
		str_map._empty = posZero - _size;
		lst.push_back(str_map);
	}
	//Move up
	if (i + 1 < _size)
	{
		str_map._map = swapMap(posZero, posZero + _size, curr_map);
		str_map._empty = posZero + _size;
		lst.push_back(str_map);
	}

	return lst;
}

int				AStar::getSize()
{
	return _size;
}

int	AStar::_size = 0;

//std::list<Node*>	AStar::getPath() const
//{
//	return std::list<Node *>();
//}

Map const	AStar::getCurrent() const
{
	return _curr;
}

void				AStar::debug() const
{
//	std:: cout << *_curr->getEmpty() << std::endl;
	std::cout << _curr;
	std::cout << "============================" << std::endl;
	std::cout << "==\tOpen\t==" << std::endl;
	for_each(_set.begin(), _set.end(), display_open);
	std::cout << "============================" << std::endl;
	std::cout << "==\tClosed\t==" << std::endl;
	for_each(_set.begin(), _set.end(), display_close);
	char c;
	std::cin >> c;
}

std::ostream	&operator<<(std::ostream &o, AStar const &c)
{
	//use this to display a significant message;
	Map const 	n = c.getCurrent();

	if (n._fscore == INT_MAX)
		o << "(nullptr)";
	else
		o << n;
	o << std::endl;
	return o;
}

AStar::NoSolution::NoSolution() throw(): std::exception(){}

AStar::NoSolution::~NoSolution() throw() {}

const char	*AStar::NoSolution::what() const throw()
{
	return "No solution found... :'(";
}

std::ostream	&operator<<(std::ostream &o, std::map<std::vector<int>, Node*> &c)
{
	(void)c;
	o << "IN QUEUE : " << std::endl;
	for (auto it: c)
		o << *(std::get<1>(it)) << std::endl;
	o << std::endl;
	return o;
}
