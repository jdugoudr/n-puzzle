/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AStar.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:12:59 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/15 19:46:22 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	ASTAR_HPP
# define ASTAR_HPP

#include "Node.hpp"
#include "IHeuristic.hpp"
#include "p_queue_custom.hpp"
#include <forward_list>
#include <list>
#include <iostream>

class AStar{

private:
	int	const									_size;
	Node const								&_start;
	Node const								&_goal;
	IHeuristic const					&_h;
	Node											*_curr;
	p_queue_custom<Node *>		_openList;
//	std::forward_list<Node *>	_closedList;
	p_queue_custom<Node *>	_closedList;

	void							for_each_neighbor(std::list<Node*> neighbors);
	Node							*swapMap(int src, int dest);
	std::list<Node *>	getNeighbor();

	void							debug(std::list<Node*> neighbors) const;

public:
	AStar(Node const &start, Node const &goal, IHeuristic const &h);
	virtual ~AStar();

	void							run();
	std::list<Node*>	getPath() const;
	Node const				*getCurrent() const;
	

	class NoSolution: public std::exception{
		public:
			NoSolution() throw();
			~NoSolution() throw();
			virtual const char *what() const throw();
	};

};

std::ostream	&operator<<(std::ostream &o, AStar const &c);

#endif

