/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:18:18 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/12 20:26:13 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	NODE_HPP
# define NODE_HPP

# include "Case.hpp"
# include <iomanip>
# include <iostream>
# include <vector>

class Node{

private:
	std::vector<std::vector<Case *>> 				_map;
	int const																_mapSize;
	int																			_costSoFar;
	int																			_costToReach;
	Case 																		*_empty;
	Node																		*_comeFrom;

	Node();

public:
	Node(Node const &other);
	Node(std::vector<std::vector<Case *>> map, int mapSize);
	Node(std::vector<std::vector<Case *>> map, int mapSize, int costSoFar, Node *prev);
	virtual ~Node();

	Node	&operator=(Node const &other);


	std::vector<std::vector<Case *>> const				getMap() const;
	int								getMapSize() const;
	int								getCostSoFar() const;
	int								getCostToReach() const;
	Node							*getPrev() const;
	Case							*getEmpty() const;
	void							setCostSoFar(int nc);
	void							setCostToReach(int nc);
	void							setEmpty(Case *);
	void							setComeFrom(Node *p);

	bool							operator<(Node const &other);
	bool							operator>(Node const &other);
	bool							operator==(Node const &other);

	void							swap(size_t csrc, size_t lsrc,
													size_t cdest, size_t ldest);
	static bool				comp(Node *a, Node *b);
};

std::ostream	&operator<<(std::ostream &o, Node const &c);

#endif

