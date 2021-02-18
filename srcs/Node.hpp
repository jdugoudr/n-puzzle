/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:18:18 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/17 22:08:27 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	NODE_HPP
# define NODE_HPP

//# include "Case.hpp"
#include <limits.h>
# include <iomanip>
# include <iostream>
# include <vector>

struct								Map{
	std::vector<int>		_map;
	int									_fscore;
//	std::vector<int>		_parent;
	Map									*_parent;
	int									_gscore;
	int									_empty;
	bool								_isOpen;

	Map():_map({0}), _fscore(INT_MAX), _parent(nullptr),_gscore(INT_MAX), _empty(0), _isOpen(1)
	{}
	Map(Map const &o, Map &p)
	{
		_map = o._map;
		_fscore = o._fscore;
		_parent = &p;
		_gscore = o._gscore;
		_empty = o._empty;
	}
	Map(std::vector<int> m, Map *p, int g, int f, int e):
																								_map(m),
																								_fscore(f),
																								_parent(p),
																								_gscore(g),
																								_empty(e),
																								_isOpen(1)
	{
	}

	bool	operator>(const Map &p) const {
		return _fscore > p._fscore;
	}
	bool	operator==(const Map &p) const {
		return _map == p._map;
	}
	static bool	comp(Map *a, Map *b){
		return *a > *b;
	}
};


class Node{

private:
	Map																			_map;
	int const																_mapSize;
	int																			_costSoFar;
	int																			_costToReach;
	Node																		*_comeFrom;

	Node();

public:
	Node(Node const &other);
	Node(std::vector<int> map, int mapSize);
	Node(std::vector<int> map, int mapSize, int costSoFar, Node *prev);
	Node(Map	 map, int mapSize, int costSoFar, Node *prev);
	virtual ~Node();

	Node	&operator=(Node const &other);


	std::vector<int> const			&getMap() const;
	int								getMapSize() const;
	int								getCostSoFar() const;
	int								getCostToReach() const;
	Node							*getPrev() const;
	int								getEmpty() const;
	void							setCostSoFar(int nc);
	void							setCostToReach(int nc);
	void							setEmpty(int);
	void							setComeFrom(Node *p);

	bool							operator<(Node const &other);
	bool							operator>(Node const &other);
	bool							operator==(Node const &other);

	void							swap(size_t src, size_t dest);
	static bool				comp(Node *a, Node *b);
	static bool				find_in_queue(Node *el, Node *toFind);
};

std::ostream	&operator<<(std::ostream &o, Node const &c);
std::ostream	&operator<<(std::ostream &o, Map const &c);

#endif

