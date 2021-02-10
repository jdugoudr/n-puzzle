/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AStar.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:12:59 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/10 22:26:44 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	ASTAR_HPP
# define ASTAR_HPP

#include "Node.hpp"
#include "Case.hpp"
#include "IHeuristic.hpp"
#include "p_queue_custom.hpp"
#include <list>
//#include <forward_list>
#include <iostream>

class AStar{

private:
	int	const								_size;
	Node										&_start;
	Node const							&_goal;
	IHeuristic							&_h;
	Node										*_curr;
	p_queue_custom<Node *>	_openList;
	p_queue_custom<Node *>	_closedList;
//	std::forward_list<Node *>	_openList;
//	std::forward_list<Node *>	_closedList;

	void		for_each_neighbor(Node *curr, std::list<Node*> neighbors);
	Node							*swapMap(size_t, size_t, size_t, size_t);
	std::list<Node *>	getNeighbor();
	void							createNeighbor(std::list<Node *> &lst,
																						size_t i,
																						size_t j);

public:
	AStar(Node &start, Node const &goal, IHeuristic &h);
	virtual ~AStar();

	void							run();
	std::list<Node*>	getPath() const;
	Node const				*getCurrent() const;
	

};

std::ostream	&operator<<(std::ostream &o, AStar const &c);

#endif

