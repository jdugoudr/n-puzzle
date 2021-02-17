/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AStar.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:12:59 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/17 02:12:11 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	ASTAR_HPP
# define ASTAR_HPP

#include "Node.hpp"
#include "IHeuristic.hpp"
#include <list>
#include <queue>
#include <map>
#include <map>
#include <iostream>

class AStar{

private:
	int	const															_size;
	Node 																	*_start;
	Node const														&_goal;
	IHeuristic const											&_h;
	Node																	*_curr;
	std::map<std::vector<int>, Node *>		_closedSet;
	std::map<std::vector<int>, Node *>		_openSet;
	std::priority_queue<Node *,
	std::vector<Node*>, bool (*)(Node*, Node*)>	_openList;


	void							pushOpenList(Node *n);
	void							pushFromOpenToClose(Node *n);
	void							pushFromCloseToOpen(Node *n);
	void							pushNewNodeToOpen(int soFar, int toReach,
																				t_map map, Node *parent);

	std::vector<int>		swapMap(int src, int dest, std::vector<int> map);
	std::vector<t_map>	getNeighbor(Node *curr);


	void							debug() const;

public:
	AStar(Node *start, Node const &goal, IHeuristic const &h);
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

