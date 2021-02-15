/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AStar.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 17:20:50 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/15 17:15:55 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AStar.hpp"
#include "find_if_mix.hpp"
#include <iostream>

AStar::~AStar()
{
}

AStar::AStar(Node const &start, Node const &goal, IHeuristic const &h):
																				_size(start.getMapSize()),
																				_start(start),
																				_goal(goal),
																				_h(h),
																				_curr(nullptr),
																				_openList(Node::comp),
																				_closedList(Node::comp)
{
	(void)_goal;
	(void)_h;
}

Node			*AStar::swapMap(int src, int dest)
{
	Node	*neighbor = new Node(*_curr);

	neighbor->swap(src, dest);
	neighbor->setCostSoFar(_curr->getCostSoFar() + 1);

	return neighbor;	
}

void display(Node *el)
{
	std::cout << *el << std::endl;
}

bool find_in_queue(Node *el, Node *toFind)
{
	return *el == *toFind;
}

void							AStar::createNeighbor(std::list<Node*> &lst,
																						int i,
																						int j,
																						int pos)
{
	if (j + 1 < _size)
		lst.push_front(swapMap(pos, pos + 1));
	if (j > 0)
		lst.push_front(swapMap(pos, pos - 1));
	if (i > 0)
		lst.push_front(swapMap(pos, pos - _size));
	if (i + 1 < _size)
		lst.push_front(swapMap(pos, pos + _size));

	return ;
}

std::list<Node *>					AStar::getNeighbor()
{
	std::list<Node*> lst;

	int	posZero = _curr->getEmpty();
	createNeighbor(lst, posZero / _size, posZero % _size, posZero);
	//	isAlreadyKnown(&lst);
	return lst;
}

void							AStar::for_each_neighbor(Node *curr, std::list<Node*> neighbors)
{
	std::list<Node*>::iterator	it = neighbors.begin();
	std::list<Node*>::iterator	ite = neighbors.end();

	while (it != ite)
	{
		(void)curr;
		//int	tentative_score = curr->getCostSoFar() + 1;
		//need to check if neighbor is in openLst and if tentative_score is better than the one record.
		p_queue_custom<Node*>::iterator	itOld;
		if ((itOld = find_if_mix(_openList.begin(), _openList.end(), *it, find_in_queue)) != _openList.end())
		{
			if ((*it)->getCostSoFar() < (*itOld)->getCostSoFar())
			{
				(*itOld)->setCostSoFar((*it)->getCostSoFar());
				(*itOld)->setComeFrom(_curr);
			}
		}
		else if ((itOld = find_if_mix(_closedList.begin(), _closedList.end(), *it, find_in_queue)) != _closedList.end())
		{
			if ((*it)->getCostSoFar() < (*itOld)->getCostSoFar())
			{
				_openList.push_uniq(*it);
			}
		}
		else
		{
			(*it)->setCostToReach(_h.calculate(**it, _goal));
			_openList.push_uniq(*it);
		}
		it++;
	}

//	std:: cout << *_curr->getEmpty() << std::endl;
//	std::cout << *_curr;
//	std::cout << "============================" << std::endl;
//		std::cout << "==\tOpen\t==" << std::endl;
//	for_each(_openList.begin(), _openList.end(), display);
//	std::cout << "============================" << std::endl;
//		std::cout << "==\tClosed\t==" << std::endl;
//	for_each(_closedList.begin(), _closedList.end(), display);
//	if (c == 'd')
//	{
//		std::cout << "====================" << std::endl;
//		std::cout << "==\tChildren\t==" << std::endl;
//		for_each(neighbors.begin(), neighbors.end(), display);
//		std::cout << "====================" << std::endl;
//	}
//	char c;
//	std::cin >> c;
	
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
		_closedList.push_uniq(_curr);
		for_each_neighbor(_curr, getNeighbor());
	}

	throw AStar::NoSolution();
	return ;
}

std::list<Node*>	AStar::getPath() const
{
	return std::list<Node *>();
}

Node const	*AStar::getCurrent() const
{
	return _curr;
}

void							AStar::isAlreadyKnown(std::list<Node*> *lst)
{
LOOP:for (Node *curr: *lst)
		 {
			for (Node *item: _openList)
			{
				if (*item == *curr)
				{
					lst->remove(curr);
					delete curr;
					goto LOOP;
				}
			}
			for (Node *item: _closedList)
			{
				if (*item == *curr)
				{
					lst->remove(curr);
					delete curr;
					goto LOOP;
				}
			}
		 }
	return ;
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
