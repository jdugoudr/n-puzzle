/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:18:18 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/17 17:45:48 by jdugoudr         ###   ########.fr       */
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
	std::vector<int>		_parent;
	int									_gscore;
	int									_fscore;
	int									_empty;

	Map():_map({0}),_parent({0}),_gscore(INT_MAX), _fscore(INT_MAX), _empty(0){}
	Map(Map const &o, std::vector<int>p)
	{
		_map = o._map;
		_parent = p;
		_gscore = o._gscore;
		_fscore = o._fscore;
		_empty = o._empty;
	}
	Map(std::vector<int> m, std::vector<int> p, int g, int f, int e):_map(m),
																								_parent(p),
																								_gscore(g),
																								_fscore(f),
																								_empty(e)
	{}
};

struct							PairMap{
	std::vector<int>	_map;
	int								_fscore;

	PairMap():_map{0}, _fscore(INT_MAX){}
	PairMap(std::vector<int> m, int f):_map(m), _fscore(f){}

	// Mendatory part to be used by pq_custom
	bool							operator>(const PairMap &p) const {
		return _fscore > p._fscore;
	}
	bool							operator==(const PairMap &p) const {
		return _map == p._map;
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


	std::vector<int> const				getMap() const;
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
std::ostream	&operator<<(std::ostream &o, PairMap const &c);

#endif

