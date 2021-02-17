/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AStar.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 17:20:50 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/17 02:25:08 by jdugoudr         ###   ########.fr       */
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
																				_size(start->getMapSize()),
																				_start(start),
																				_goal(goal),
																				_h(h),
																				_curr(nullptr),
																				_closedSet(),
																				_openSet(),
																				_openList(Node::comp)
{
}

std::vector<int>		AStar::swapMap(int src, int dest, std::vector<int> map)
{
	std::vector<int>	newMap = map;
	
	std::swap(newMap[src], newMap[dest]);

	return newMap;	
}

void display(std::pair<std::vector<int>, Node*> el)
{
	std::cout << *(std::get<1>(el)) << std::endl;
}

void							AStar::run()
{
	_start->setCostToReach(_h.calculate(_start->getMap(), _goal));
	pushOpenList(_start);

	while (!_openList.empty())
	{
		_curr = _openList.top();
		if(*_curr == _goal)
		{
			// The resolution is over. You WIN
			std::cout << *_curr;
			return ;
		}
		pushFromOpenToClose(_curr);//pop priority_queue

		int	tentative_g = _curr->getCostSoFar() + 1;
		for (auto it: getNeighbor(_curr))
		{
			auto inClosed = _closedSet.find(it.map);
			auto inOpen = _openSet.find(it.map);
			if ( inClosed != _closedSet.end()
					||  inOpen != _openSet.end())
			{
				Node	*oldNode = inClosed != _closedSet.end() ? _closedSet[it.map] : _openSet[it.map];
				if (oldNode->getCostSoFar() > tentative_g)
				{
					oldNode->setComeFrom(_curr);
					oldNode->setCostSoFar(tentative_g);
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
				pushNewNodeToOpen(tentative_g, _h.calculate(it.map, _goal), it, _curr);
			}
		}
	//	debug();
	}

	throw AStar::NoSolution();
	return ;
}

void							AStar::pushNewNodeToOpen(int soFar, int toReach, t_map map, Node *parent)
{
	try {
		Node	*node = new Node(map, _size, soFar, parent);

		node->setCostToReach(toReach);
		_openList.push(node);
		_openSet[map.map] = node;
	} catch (std::exception &e) {
		throw e;
	}
	return ;
}

void							AStar::pushOpenList(Node *n)
{
	_openList.push(n);
	_openSet.insert(std::make_pair(n->getMap(), n));
	return ;
}

void							AStar::pushFromOpenToClose(Node *n)
{
	_closedSet[n->getMap()] = n;
	_openSet.erase(n->getMap());
	_openList.pop();
	return ;
}

void							AStar::pushFromCloseToOpen(Node *n)
{
	_openSet[n->getMap()] = n;
	_closedSet.erase(n->getMap());
	_openList.push(n);
	return ;
}

/*
 * If it element is already in openList
 * 	itPos is set to this position and return true
 * 
 * If it element is not in openList
 *  itPos is set to the iterator just after the position it should be insert,
 *  to use insert list function.
*/
//bool							AStar::is_in_open(std::list<Node*>::iterator &it,
//																			p_queue_custom<Node*>::iterator	&itPos)
//{
//	bool res = _openList.try_insert(*it, itPos);
//	if (!res)
//	{
//		if ((*it)->getCostSoFar() < (*itPos)->getCostSoFar())
//		{
//		//	std::cout << "We have to replace" << std::endl;
//		//	char c;
//		//	std::cin >> c;
//		//	debug();
//			(*itPos)->setCostSoFar((*it)->getCostSoFar());
//			(*itPos)->setComeFrom(_curr);
//			_openList.replace(itPos);
//		//	debug();
//		}
//		return true;
//	}
//	return false;
//}
//
//bool							AStar::is_in_closed(std::list<Node*>::iterator &it)
//{
////	std::list<Node*>::iterator itOld;
//	Node	*old;
//
//	try{
//		old = _closedList.at((*it)->getMap());
//		if ((*it)->getCostSoFar() < old->getCostSoFar())
//		{
//			_openList.push_uniq(*it);
//			delete old;
//			_closedList.erase((*it)->getMap());
//		}
//		else
//			delete *it;
//		return true;
//	} catch (std::out_of_range(&e)){
//		return false;
//	}
////	itOld = find_if_mix(_closedList.begin(), _closedList.end(), *it, Node::find_in_queue);
////	if (itOld != _closedList.end())
////	{
////		if ((*it)->getCostSoFar() < (*itOld)->getCostSoFar())
////		{
////			_openList.push_uniq(*it);
////			delete *itOld;
////			_closedList.erase(itOld);
////		}
////		else
////			delete *it;
////		return true;
////	}
////	return false;
//}

std::vector<t_map>			AStar::getNeighbor(Node *curr)
{
	std::vector<t_map>	lst;
	t_map								str_map;
	std::vector<int>		curr_map = curr->getMap();

	int posZero = curr->getEmpty();
	int i = posZero / _size;
	int j = posZero % _size;

	//Move to right
	if (j + 1 < _size)
	{
		str_map.map = swapMap(posZero, posZero + 1, curr_map);
		str_map.empty = posZero + 1;
		lst.push_back(str_map);
	}
	//Move to left
	if (j > 0)
	{
		str_map.map = swapMap(posZero, posZero - 1, curr_map);
		str_map.empty = posZero - 1;
		lst.push_back(str_map);
	}
	//Move down
	if (i > 0)
	{
		str_map.map = swapMap(posZero, posZero - _size, curr_map);
		str_map.empty = posZero - _size;
		lst.push_back(str_map);
	}
	//Move up
	if (i + 1 < _size)
	{
		str_map.map = swapMap(posZero, posZero + _size, curr_map);
		str_map.empty = posZero + _size;
		lst.push_back(str_map);
	}

	return lst;
}


std::list<Node*>	AStar::getPath() const
{
	return std::list<Node *>();
}

Node const	*AStar::getCurrent() const
{
	return _curr;
}

void				AStar::erase(Node *el)
{
	delete el;
}

void				AStar::erase_pair(std::pair<std::vector<int>, Node *> el)
{
	delete std::get<1>(el);
}

void				AStar::debug() const
{
//	std:: cout << *_curr->getEmpty() << std::endl;
	std::cout << *_curr;
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
	Node const 	*n = c.getCurrent();

	if (n == nullptr)
		o << "(nullptr)";
	else
		o << *n;
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
