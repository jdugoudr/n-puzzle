/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AStar.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:12:59 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/16 15:42:07 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	ASTAR_HPP
# define ASTAR_HPP

#include "Node.hpp"
#include "IHeuristic.hpp"
#include "p_queue_custom.hpp"
#include <list>
#include <map>
#include <iostream>

class AStar{

private:
	int	const																_size;
	Node const															&_start;
	Node const															&_goal;
	IHeuristic const												&_h;
	Node																		*_curr;
	p_queue_custom<Node *>									_openList;
	std::map<std::vector<int>, Node *>			_closedList;
//	std::list<Node *>					_closedList;

	void							for_each_neighbor(std::list<Node*> neighbors);
	Node							*swapMap(int src, int dest);
	std::list<Node *>	getNeighbor();
	bool							is_in_open(std::list<Node*>::iterator &it,
																	p_queue_custom<Node*>::iterator	&itPos);
	bool							is_in_closed(std::list<Node*>::iterator &it);

	void							debug() const;

public:
	AStar(Node const &start, Node const &goal, IHeuristic const &h);
	virtual ~AStar();

	void							run();
	std::list<Node*>	getPath() const;
	Node const				*getCurrent() const;
	
	static void				erase(Node *el);
	static void				erase_pair(std::pair<std::vector<int>, Node *> el);

	class NoSolution: public std::exception{
		public:
			NoSolution() throw();
			~NoSolution() throw();
			virtual const char *what() const throw();
	};

};

std::ostream	&operator<<(std::ostream &o, AStar const &c);

#endif

