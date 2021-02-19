/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AStar.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 17:20:50 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/18 18:07:01 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AStar.hpp"
//#include "find_if_mix.hpp"
#include <algorithm>
#include <iostream>

int AStar::_totalStatesSelected = 0;
int AStar::_maximumStatesRepresented = 0;

void	erase(std::pair<std::vector<int>, Node *> el)
{
	delete std::get<1>(el);
}

AStar::~AStar()
{
	while (!_openList.empty())
		_openList.pop();
	std::for_each(_set.begin(), _set.end(), erase);
	_set.clear();
}

AStar::AStar(Node *start, Node const &goal, IHeuristic const &h):
																				_goal(goal),
																				_h(h),
																				_start(start),
																				_set(),
																				_openList(Node::comp)
{
	AStar::_size = start->_mapSize;
}

std::vector<Node*>		AStar::run()
{
	pushNewNodeToOpen(0, _h.calculate(_start->_map, _goal), *_start, nullptr);
	_maximumStatesRepresented++; //complexity in size++

	while (!_openList.empty())
	{
		Node &_curr = *_openList.top();
		_totalStatesSelected++;	// complexity in time++
		if(_curr._map == _goal._map)
		{
			return getPath(&_curr);
		}

		pushFromOpenToClose(_curr);//pop priority_queue

		int	tentative_g = _curr._gscore + 1;
		for (auto it: getNeighbor(_curr))
		{
			auto el = _set.find(it._map);
			if ( el != _set.end())
			{
				Node	&oldNode = *(std::get<1>(*el));
				if (oldNode._gscore > tentative_g)
				{
					oldNode._parent = &_curr;
					oldNode._fscore = oldNode._gscore - (oldNode._gscore - tentative_g);
					oldNode._gscore = tentative_g;
					if (!oldNode._isOpen)
						pushFromCloseToOpen(oldNode);
				}
				else
					continue ;
			}
			else
			{
				pushNewNodeToOpen(tentative_g, _h.calculate(it._map, _goal), it, &_curr);
				_maximumStatesRepresented++; //complexity in size++
			}
		}
	//	debug();
	}

	throw AStar::NoSolution();
	return std::vector<Node*>();
}

void							AStar::pushNewNodeToOpen(int soFar, int toReach, Node &map, Node *parent)
{
	try {
		Node	&ref = *(new Node(map, parent));

		ref._gscore = soFar;
		ref._fscore = soFar + toReach;
		ref._mapSize = _size;

		_openList.push(&ref);
		ref._isOpen = true;

		_set[map._map] = &ref;


	} catch (std::exception &e) {
		throw e;
	}
	return ;
}

void							AStar::pushOpenList(Node &node)
{
	(void)node;
	return ;
}

void							AStar::pushFromOpenToClose(Node &m)
{
	m._isOpen = false;
	_openList.pop();
	return ;
}

void							AStar::pushFromCloseToOpen(Node &n)
{
	n._isOpen = true;
	_openList.push(&n);
	return ;
}

std::vector<Node>			AStar::getNeighbor(Node &m)
{
	std::vector<Node>					lst;
	Node											str_map;
	std::vector<int> const		&curr_map = m._map;

	int posZero = m._empty;
	int i = posZero / _size;
	int j = posZero % _size;

	//Move to right
	if (j + 1 < _size)
	{
//		str_map._map = swapMap(posZero, posZero + 1, curr_map);
		str_map._map = curr_map;
		std::swap(str_map._map[posZero], str_map._map[posZero + 1]);
		str_map._empty = posZero + 1;
		lst.push_back(str_map);
	}
	//Move to left
	if (j > 0)
	{
		str_map._map = curr_map;
		std::swap(str_map._map[posZero], str_map._map[posZero - 1]);
		str_map._empty = posZero - 1;
		lst.push_back(str_map);
	}
	//Move down
	if (i > 0)
	{
		str_map._map = curr_map;
		std::swap(str_map._map[posZero], str_map._map[posZero - _size]);
		str_map._empty = posZero - _size;
		lst.push_back(str_map);
	}
	//Move up
	if (i + 1 < _size)
	{
		str_map._map = curr_map;
		std::swap(str_map._map[posZero], str_map._map[posZero + _size]);
		str_map._empty = posZero + _size;
		lst.push_back(str_map);
	}

	return lst;
}

int				AStar::getSize()
{
	return _size;
}

std::vector<Node*>		AStar::getPath(Node *ptr)
{
	if (ptr == nullptr)
		return _finaleResult;
	getPath(ptr->_parent);
	_finaleResult.push_back(ptr);
	return _finaleResult;
}

int	AStar::_size = 0;

void display_open(std::pair<std::vector<int>, Node*> const &el)
{
	Node	const &m = *std::get<1>(el);

	if (m._isOpen)
		std::cout << m << std::endl;
}
void display_close(std::pair<std::vector<int>, Node*> const &el)
{
	Node	const &m = *std::get<1>(el);

	if (!m._isOpen)
		std::cout << m << std::endl;
}

void				AStar::debug() const
{
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
	(void)c;

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
