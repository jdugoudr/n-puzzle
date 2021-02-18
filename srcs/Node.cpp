/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:35:56 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/18 17:23:44 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Node.hpp"
#include "AStar.hpp"
#include <limits.h>
# include <vector>

Node::Node():_map({0}), _fscore(INT_MAX), _parent(nullptr),_gscore(0),
													_empty(0), _isOpen(1), _mapSize(0)
{}

Node::Node(std::vector<int> m, int s):_map(m), _fscore(INT_MAX),
															_parent(nullptr),_gscore(0),
															_empty(0), _isOpen(1), _mapSize(s)
{}

Node::Node(Node const &o, Node *p)
{
	_map = o._map;
	_fscore = o._fscore;
	_parent = p;
	_gscore = o._gscore;
	_empty = o._empty;
	_mapSize = o._mapSize;
}

Node::Node(std::vector<int> m, Node *p, int g, int f, int e, int s):
																								_map(m),
																								_fscore(f),
																								_parent(p),
																								_gscore(g),
																								_empty(e),
																								_isOpen(1),
																								_mapSize(s)
{
}

bool	Node::operator>(const Node &p) const {
	return _fscore > p._fscore;
}
bool	Node::operator==(const Node &p) const {
	return _map == p._map;
}
bool	Node::comp(Node *a, Node *b){
	return *a > *b;
}

std::vector<int> const								&Node::getMap() const
{
	return _map;
}

int													Node::getMapSize() const
{
	return _mapSize;
}

int													Node::getEmpty() const
{
	return _empty;
}

void												Node::setEmpty(int empty)
{
	_empty = empty;
	return ;
}

void												Node::swap(size_t src, size_t dest)
{
	std::swap(_map[src], _map[dest]);
	return ;
}

std::ostream	&operator<<(std::ostream &o, Node const &c)
{
	int		width = 1;
	int		size = c._mapSize;
	int		total_size = size * size - 1;

	while (total_size > 0)
	{
		total_size /= 10;
		width++;
	}

	int	i = 0;
	for (auto &it1: c._map)
	{
		o << std::setw(width) << it1;
		i++;
		if (i % size == 0)
			o << std::endl;
	}
	if (c._fscore != INT_MAX)
		o <<std::setw(width) <<  c._gscore << " - " << c._fscore - c._gscore << std::endl;
	return o;
}
