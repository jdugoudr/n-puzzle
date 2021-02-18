/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:18:18 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/15 19:13:45 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	NODE_HPP
# define NODE_HPP

//# include "Case.hpp"
# include <iomanip>
# include <iostream>
# include <vector>

class Node{

private:
	std::vector<int>												_map;
	int const																_mapSize;
	int																			_costSoFar;
	int																			_costToReach;
	int 																		_empty;
	Node																		*_comeFrom;

	Node();

public:
	Node(Node const &other);
	Node(std::vector<int> map, int mapSize);
	Node(std::vector<int> map, int mapSize, int costSoFar, Node *prev);
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

#endif

