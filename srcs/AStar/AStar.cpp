/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AStar.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 17:20:50 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/24 21:21:15 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AStar.hpp"
#include <algorithm>
#include <iostream>

int AStar::_totalStatesSelected = 0;

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

	while (!_openList.empty())
	{
		Node &_curr = *_openList.pop();// pop
		_totalStatesSelected++;	// complexity in time++
		if(_curr._map == _goal._map)
		{
			return getPath(&_curr);
		}

		_curr._isOpen = false;//push to closed

		int	tentative_g = _curr._gscore + 1;

		std::array<Node, 4>	lst_neighbor;
		int nbNeighbor = 0;
		getNeighbor(_curr, lst_neighbor, nbNeighbor);

		for (int i = 0; i < nbNeighbor ; i++)
		{
			Node &it = lst_neighbor[i];
			auto el = _set.find(it._map);
			if ( el != _set.end())
			{
				Node	&oldNode = *(std::get<1>(*el));
				if (oldNode._isOpen && oldNode._gscore > tentative_g)
				{
					oldNode._parent = &_curr;
					oldNode._fscore = oldNode._fscore - (oldNode._gscore - tentative_g);
					oldNode._gscore = tentative_g;

					_openList.sort();
				}
				else
					continue ;
			}
			else
				pushNewNodeToOpen(tentative_g, _h.calculate(it._map, _goal), it, &_curr);
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

void							AStar::getNeighbor(Node const &m,
										std::array<Node,4> &lst, int &nb)
{
	std::vector<int> const &curr_map = m._map;

	int posZero = m._empty;
	int i = posZero / _size;
	int j = posZero % _size;

	//Move to right
	if (j + 1 < _size)
	{
		lst[nb]._map = curr_map;
		std::swap(lst[nb]._map[posZero], lst[nb]._map[posZero + 1]);
		lst[nb]._empty = posZero + 1;
		nb += 1;
	}
	//Move to left
	if (j > 0)
	{
		lst[nb]._map = curr_map;
		std::swap(lst[nb]._map[posZero], lst[nb]._map[posZero - 1]);
		lst[nb]._empty = posZero - 1;
		nb += 1;
	}
	//Move down
	if (i > 0)
	{
		lst[nb]._map = curr_map;
		std::swap(lst[nb]._map[posZero], lst[nb]._map[posZero - _size]);
		lst[nb]._empty = posZero - _size;
		nb += 1;
	}
	//Move up
	if (i + 1 < _size)
	{
		lst[nb]._map = curr_map;
		std::swap(lst[nb]._map[posZero], lst[nb]._map[posZero + _size]);
		lst[nb]._empty = posZero + _size;
		nb += 1;
	}

	//return lst;
	return ;
}

int				AStar::getSize()
{
	return _size;
}

int				AStar::getSetSize()
{
	return _set.size();
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
