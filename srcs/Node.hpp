/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:18:18 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/10 19:30:45 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	NODE_HPP
# define NODE_HPP

#include "Case.hpp"
#include <iostream>
#include <vector>

class Node{

private:
	std::vector<std::vector<Case *>> const												_map;
	int const																			_mapSize;
	int																					_costSoFar;
	int																					_costToReach;
	Case																				*_empty;
	Node																				*_comeFrom;

	Node();
	Node(Node const &other);
	Node	&operator=(Node const &other);

public:
	Node(std::vector<std::vector<Case *>> map, int mapSize);
	Node(std::vector<std::vector<Case *>> map, int mapSize, int costSoFar, Node *prev);
	virtual ~Node();

	std::vector<std::vector<Case *>> const				getMap() const;
	int													getMapSize() const;
	int													getCostSoFar() const;
	int													getCostToReach() const;
	Case												*getEmpty() const;
	void												setCostSoFar(int nc);
	void												setCostToReach(int nc);
	void												setEmpty(Case *);

	bool												operator<(Node const &other);
	bool												operator>(Node const &other);
	bool												operator==(Node const &other);

	static bool									comp(Node *a, Node *b);
};

std::ostream	&operator<<(std::ostream &o, Node const &c);

#endif

