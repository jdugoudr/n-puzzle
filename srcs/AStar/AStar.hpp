/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AStar.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:12:59 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/18 17:18:19 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	ASTAR_HPP
# define ASTAR_HPP

#include "Node.hpp"
//#include "pq_custom.hpp"
#include "IHeuristic.hpp"
#include <list>
#include <queue>
#include <map>
#include <iostream>

class AStar{

private:
	static	int																								_size;
	Node const																								&_goal;
	IHeuristic const																					&_h;
	Node																											*_start;

	std::map<std::vector<int>, Node*>													_set;
	std::priority_queue<
		Node*,std::vector<Node*>, bool (*)(Node*,Node*)>						_openList;


	void					pushOpenList(Node &node);
	void					pushFromOpenToClose(Node &m);
	void					pushFromCloseToOpen(Node &m);
	void					pushNewNodeToOpen(int const soFar, int const toReach,
																				Node &map, Node *parent);

	std::vector<Node>		getNeighbor(Node &m);


	void							debug() const;

public:
	AStar(Node *start, Node const &goal, IHeuristic const &h);
	virtual ~AStar();

	void							run();
	
	static int				getSize();
//	std::list<Node*>	getPath() const;

	class NoSolution: public std::exception{
		public:
			NoSolution() throw();
			~NoSolution() throw();
			virtual const char *what() const throw();
	};

};


std::ostream	&operator<<(std::ostream &o, AStar const &c);

#endif

