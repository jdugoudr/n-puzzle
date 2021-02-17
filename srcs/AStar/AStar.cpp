/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AStar.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 17:20:50 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/17 17:54:34 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AStar.hpp"
#include "find_if_mix.hpp"
#include <algorithm>
#include <iostream>

AStar::~AStar()
{
//	std::for_each(_closedList.begin(), _closedList.end(), AStar::erase_pair);
//	std::for_each(_openList.begin(), _openList.end(), AStar::erase);
	_closedSet.clear();
	_openSet.clear();
	while (!_openList.empty())
		_openList.pop();
}

AStar::AStar(Node *start, Node const &goal, IHeuristic const &h):
																				_goal(goal),
																				_h(h),
																				_start(start),
																				_curr(),
																				_closedSet(),
																				_openSet(),
																				_openList()
{
	AStar::_size = start->getMapSize();
}

std::vector<int>		AStar::swapMap(int src, int dest, std::vector<int> map)
{
	std::vector<int>	newMap = map;
	
	std::swap(newMap[src], newMap[dest]);

	return newMap;	
}

void display(std::pair<std::vector<int>, Map> el)
{
	std::cout << (std::get<1>(el)) << std::endl;
}

void							AStar::run()
{
	_start->setCostToReach(_h.calculate(_start->getMap(), _goal));
	Map start(_start->getMap(),
				{0}, 0, _start->getCostToReach(),
				_start->getEmpty());

	pushOpenList(start);

	while (!_openList.empty())
	{
		_curr = _openList.top();
		auto	&_currMap = _curr._map;
		if(_currMap == _goal.getMap())
		{
			// The resolution is over. You WIN
			std::cout << _openSet[_curr._map];
			return ;
		}
		pushFromOpenToClose(_curr);//pop priority_queue

		int	tentative_g = _closedSet[_currMap]._gscore + 1;
		for (auto it: getNeighbor(_closedSet[_currMap]))
		{
			auto inClosed = _closedSet.find(it._map);
			auto inOpen = _openSet.find(it._map);
			if ( inClosed != _closedSet.end()
					||  inOpen != _openSet.end())
			{
				Map	&oldNode = inClosed != _closedSet.end() ? _closedSet[it._map] : _openSet[it._map];
				if (oldNode._gscore > tentative_g)
				{
					oldNode._parent = _currMap;
					oldNode._fscore = oldNode._gscore - (oldNode._gscore - tentative_g);
					oldNode._gscore = tentative_g;
					if (inClosed != _closedSet.end())
					{
//						std::cout << "Oh my god Yes !" << std::endl;
						pushFromCloseToOpen(oldNode);
					}
				}
				else
					continue ;
			}
			else
			{
				pushNewNodeToOpen(tentative_g, _h.calculate(it._map, _goal), it, _curr._map);
			}
		}
//		debug();
	}
	throw AStar::NoSolution();
	return ;
}

void							AStar::pushNewNodeToOpen(int soFar, int toReach, Map &map, std::vector<int> &parent)
{
	try {
		Map	newMap(map, parent);
		newMap._gscore = soFar;
		newMap._fscore = soFar + toReach;

		_openList.push(PairMap(map._map, newMap._fscore));

		_openSet[map._map] = newMap;
	} catch (std::exception &e) {
		throw e;
	}
	return ;
}

void							AStar::pushOpenList(Map &node)
{
	_openList.push(PairMap(node._map, node._fscore));
	_openSet.insert(std::make_pair(node._map, node));
	return ;
}

void							AStar::pushFromOpenToClose(PairMap &m)
{
	_closedSet[m._map] = _openSet[m._map];
	_openSet.erase(m._map);
	_openList.pop();
	return ;
}

void							AStar::pushFromCloseToOpen(Map &n)
{
	_openSet[n._map] = n;
	_closedSet.erase(n._map);
	_openList.push(PairMap(n._map, n._fscore));
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

PairMap const	AStar::getCurrent() const
{
	return _curr;
}
//
//void				AStar::erase(Node *el)
//{
//	delete el;
//}
//
//void				AStar::erase_pair(std::pair<std::vector<int>, Node *> el)
//{
//	delete std::get<1>(el);
//}

void				AStar::debug() const
{
//	std:: cout << *_curr->getEmpty() << std::endl;
	std::cout << _curr;
	std::cout << "============================" << std::endl;
		std::cout << "==\tOpen\t==" << std::endl;
	for_each(_openSet.begin(), _openSet.end(), display);
	std::cout << "============================" << std::endl;
		std::cout << "==\tClosed\t==" << std::endl;
	for_each(_closedSet.begin(), _closedSet.end(), display);
	char c;
	std::cin >> c;
}

std::ostream	&operator<<(std::ostream &o, AStar const &c)
{
	//use this to display a significant message;
	PairMap const 	n = c.getCurrent();

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
//	p_queue_custom<Node*>::iterator	it = c.begin();
//	p_queue_custom<Node*>::iterator	eit = c.end();
//	while (it != eit)
//	{
//		o << **it << std::endl;
//		it++;
//	}
	o << std::endl;
	return o;
}
