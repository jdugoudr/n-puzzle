/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AStar.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 17:20:50 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/16 01:31:36 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AStar.hpp"
#include "find_if_mix.hpp"
#include <iostream>

AStar::~AStar()
{
//	std::for_each(_closedList.begin(), _closedList.end(), AStar::erase);
	std::for_each(_openList.begin(), _openList.end(), AStar::erase);
	_closedList.clear();
	_openList.clear();
}

AStar::AStar(Node const &start, Node const &goal, IHeuristic const &h):
																				_size(start.getMapSize()),
																				_start(start),
																				_goal(goal),
																				_h(h),
																				_curr(nullptr),
																				_openList(Node::comp),
																				_closedList()
{
}

Node			*AStar::swapMap(int src, int dest)
{
	Node	*neighbor = new Node(*_curr);

	neighbor->swap(src, dest);
	neighbor->setCostSoFar(_curr->getCostSoFar() + 1);
	neighbor->setCostToReach(_h.calculate(*neighbor, _goal));

	return neighbor;	
}

void display(Node *el)
{
	std::cout << *el << std::endl;
}

void							AStar::run()
{
	_curr	= new Node(_start);
	_curr->setCostToReach(_h.calculate(_start, _goal));
	_openList.push_uniq(_curr);

	while (!_openList.empty())
	{
		_curr = _openList.top();
		if (*_curr == _goal)
		{
			std::cout << "You got it !!!" << std::endl;
std::cout <<"==============================" << std::endl;
			std::cout << *_curr;

			return ;
		}
		_openList.pop();
		_closedList.insert(std::make_pair(_curr->getMap(), _curr));
	//	_closedList.push_front(_curr);
		std::list<Node*> neighbors = getNeighbor();
		for_each_neighbor(neighbors);
	}

	throw AStar::NoSolution();
	return ;
}

void							AStar::for_each_neighbor(std::list<Node*> neighbors)
{
	std::list<Node*>::iterator	it = neighbors.begin();
	std::list<Node*>::iterator	ite = neighbors.end();
	p_queue_custom<Node*>::iterator	itPos;

	while (it != ite)
	{
		if (!is_in_closed(it))
		{
			if (is_in_open(it, itPos))
			{
				delete *it;
			}
			else
			{
				_openList.insert(itPos, *it);
			}
		}
		it++;
	}

	//debug(neighbors);
	
}

/*
 * If it element is already in openList
 * 	itPos is set to this position and return true
 * 
 * If it element is not in openList
 *  itPos is set to the iterator just after the position it should be insert,
 *  to use insert list function.
*/
bool							AStar::is_in_open(std::list<Node*>::iterator &it, p_queue_custom<Node*>::iterator	&itPos)
{
	bool res = _openList.try_insert(*it, itPos);
	if (!res)
	{
		if ((*it)->getCostSoFar() < (*itPos)->getCostSoFar())
		{
			(*itPos)->setCostSoFar((*it)->getCostSoFar());
			(*itPos)->setComeFrom(_curr);
			// Have to re-place itOld at the right new place in openList
		}
		return true;
	}
	return false;
}

bool							AStar::is_in_closed(std::list<Node*>::iterator &it)
{
//	std::list<Node*>::iterator itOld;
	Node	*old;

	try{
		old = _closedList.at((*it)->getMap());
		if ((*it)->getCostSoFar() < old->getCostSoFar())
		{
			_openList.push_uniq(*it);
			delete old;
			_closedList.erase((*it)->getMap());
		}
		else
			delete *it;
		return true;
	} catch (std::out_of_range(&e)){
		return false;
	}
//	itOld = find_if_mix(_closedList.begin(), _closedList.end(), *it, Node::find_in_queue);
//	if (itOld != _closedList.end())
//	{
//		if ((*it)->getCostSoFar() < (*itOld)->getCostSoFar())
//		{
//			_openList.push_uniq(*it);
//			delete *itOld;
//			_closedList.erase(itOld);
//		}
//		else
//			delete *it;
//		return true;
//	}
//	return false;
}

std::list<Node *>					AStar::getNeighbor()
{
	std::list<Node*> lst;

	int posZero = _curr->getEmpty();
	int i = posZero / _size;
	int j = posZero % _size;

	//Move to right
	if (j + 1 < _size)
		lst.push_front(swapMap(posZero, posZero + 1));
	//Move to left
	if (j > 0)
		lst.push_front(swapMap(posZero, posZero - 1));
	//Move down
	if (i > 0)
		lst.push_front(swapMap(posZero, posZero - _size));
	//Move up
	if (i + 1 < _size)
		lst.push_front(swapMap(posZero, posZero + _size));

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

void				AStar::debug(std::list<Node*> neighbors) const
{
	(void)neighbors;
//	std:: cout << *_curr->getEmpty() << std::endl;
	std::cout << *_curr;
//	std::cout << "============================" << std::endl;
		std::cout << "==\tOpen\t==" << std::endl;
	for_each(_openList.begin(), _openList.end(), display);
	std::cout << "============================" << std::endl;
//		std::cout << "==\tClosed\t==" << std::endl;
//	for_each(_closedList.begin(), _closedList.end(), display);
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

std::ostream	&operator<<(std::ostream &o, p_queue_custom<Node*> &c)
{
	(void)c;
	p_queue_custom<Node*>::iterator	it = c.begin();
	p_queue_custom<Node*>::iterator	eit = c.end();
	o << "IN QUEUE : " << std::endl;
	while (it != eit)
	{
		o << **it << std::endl;
		it++;
	}
	o << std::endl;
	return o;
}
