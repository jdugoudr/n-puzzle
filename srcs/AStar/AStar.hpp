/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AStar.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:12:59 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/12 16:55:12 by jdugoudr         ###   ########.fr       */
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
	Node const							&_start;
	Node const							&_goal;
	IHeuristic const				&_h;
	Node										*_curr;
	p_queue_custom<Node *>	_openList;
	p_queue_custom<Node *>	_closedList;

	void		isAlreadyKnown(std::list<Node*> *lst);
	void		for_each_neighbor(Node *curr, std::list<Node*> neighbors);
	Node							*swapMap(int, int, int, int);
	std::list<Node *>	getNeighbor();
	void							createNeighbor(std::list<Node *> &lst,
																						int i,
																						int j);

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

