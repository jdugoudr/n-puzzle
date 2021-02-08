/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:18:18 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/08 22:09:27 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	NODE_HPP
# define NODE_HPP

#include "Case.hpp"
#include <iostream>
#include <array>

class Node{

private:
	std::array<std::array<Case *, 2>, 2> const	_map;
	int																					_costSoFar;
	int																					_costToReach;

	Node();
	Node(Node const &other);
	Node	&operator=(Node const &other);

public:
	Node(std::array<std::array<Case *, 2>, 2> map);
	Node(std::array<std::array<Case *, 2>, 2> map, int costSoFar);
	virtual ~Node();

	std::array<std::array<Case *, 2>, 2> const	getMap() const;
	int													getCostSoFar() const;
	int													getCostToReach() const;
	void												setCostSoFar(int nc);
	void												setCostToReach(int nc);

	bool												operator<(Node const &other);
	bool												operator==(Node const &other);

};

std::ostream	&operator<<(std::ostream &o, Node const &c);

#endif

