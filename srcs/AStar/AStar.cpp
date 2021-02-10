/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AStar.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 17:20:50 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/10 16:38:23 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AStar.hpp"
#include <iostream>

AStar::~AStar()
{
}

AStar::AStar(Node &start, Node const &goal, IHeuristic &h):
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

void									AStar::createNeighbor(std::list<Node*> &lst,
																						size_t i,
																						size_t j)
{
	std::cout << _curr->getMap() << std::endl;
	std::cout << "you find it at : " << i << "-" << j << std::endl;
	std::cout << "neighbor :" << std::endl;

	if (j + 1 < 2)
	{
		std::array<std::array<Case*, 2>, 2> newMap = _curr->getMap();
		std::swap(newMap[i][j], newMap[i][j+1]);
		Node *neighbor = new Node(newMap, _curr->getCostSoFar() + 1, _curr);
		lst.push_front(neighbor);
		std::cout << newMap << std::endl;
	}
	if (j > 0)
	{
		std::array<std::array<Case*, 2>, 2> newMap = _curr->getMap();
		std::swap(newMap[i][j], newMap[i][j-1]);
		Node *neighbor = new Node(newMap, _curr->getCostSoFar() + 1, _curr);
		lst.push_front(neighbor);
		std::cout << newMap << std::endl;
	}
	if (i > 0)
	{
		std::array<std::array<Case*, 2>, 2> newMap = _curr->getMap();
		std::swap(newMap[i][j], newMap[i-1][j]);
		Node *neighbor = new Node(newMap, _curr->getCostSoFar() + 1, _curr);
		lst.push_front(neighbor);
		std::cout << newMap << std::endl;
	}
	if (i + 1 < 2)
	{
		std::array<std::array<Case*, 2>, 2> newMap = _curr->getMap();
		std::swap(newMap[i][j], newMap[i-1][j]);
		Node *neighbor = new Node(newMap, _curr->getCostSoFar() + 1, _curr);
		lst.push_front(neighbor);
		std::cout << newMap << std::endl;
	}
	std::cout << "====================="<< std::endl;
	
	return ;
}

std::list<Node *>					AStar::getNeighbor()
{
	size_t	i = 0;
	size_t	j = 0;
	std::list<Node*> lst;

	std::array<std::array<Case*, 2>, 2>	const map = _curr->getMap();
	while (i < 2)
	{
		while (j < 2)
		{
			if (map[i][j]->getValue() == 0)
			{
				createNeighbor(lst, i, j);
				return lst;
			}
			j++;
		}
		j = 0;
		i++;
	}
	std::cerr << "Error : " << i << "-" << j << std::endl;

	throw std::out_of_range("Out of Range while looking for neighbor ");
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
		(*it)->setCostToReach(_h.calculate(*it, &_goal));
		_openList.push(*it);
		it++;
	}
}

void							AStar::run()
{
	_openList.push(&_start);

	_start.setCostToReach(_h.calculate(&_start, &_goal));

	while (!_openList.empty())
	{
		_curr = _openList.top();
		if (*_curr == _goal)
		{
			std::cout << "You got it !!!" << std::endl;
			return ;
		}
		_openList.pop();
//		std::cout << *_curr << std::endl;
		for_each_neighbor(_curr, getNeighbor());
	}

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

