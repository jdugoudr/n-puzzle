/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:35:56 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/08 22:09:44 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Node.hpp"
#include <iostream>

using namespace	std;

Node::Node():_map()
{
}

Node::Node(Node const &other):_map()
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
		//put here whatever make your object equal to an other
	}
	return *this;
}

Node::Node(array<array<Case *, 2>, 2> map):_map(map),
															_costSoFar(0),
															_costToReach(0)
{}

Node::Node(array<array<Case *, 2>, 2> map, int costSoFar):
																				_map(map),
																				_costSoFar(costSoFar),
																				_costToReach(0)
{}

array<array<Case *, 2>, 2> const	Node::getMap() const
{
	return _map;
}

int													Node::getCostSoFar() const
{
	return _costSoFar;
}

int													Node::getCostToReach() const
{
	return _costToReach;
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

bool												Node::operator<(Node const &other)
{
	int	totalO = other.getCostSoFar() + other.getCostToReach();
	int	totalT = this->_costSoFar + this->_costToReach;

	return totalT < totalO;
}

bool												Node::operator==(Node const &other)
{
	(void)other;
	std::cerr << "have to implement a map comparaison"
		<< std::endl;
	return false;
}


std::ostream	&operator<<(std::ostream &o, Node const &c)
{
	(void)c;
	o << "Have to implement a beautyful display of the map"
		<< std::endl;
	return o;
}

