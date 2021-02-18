/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AStar.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:12:59 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/18 15:11:36 by jdugoudr         ###   ########.fr       */
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

	std::map<std::vector<int>, Map*>													_set;
	std::priority_queue<
		Map*,std::vector<Map*>, bool (*)(Map*,Map*)>						_openList;


	void					pushOpenList(Map &node);
	void					pushFromOpenToClose(Map &m);
	void					pushFromCloseToOpen(Map &m);
	void					pushNewNodeToOpen(int const soFar, int const toReach,
																				Map &map, Map &parent);

//	std::vector<int>		swapMap(int src, int dest, std::vector<int> map);
	std::vector<Map>		getNeighbor(Map &m);


	void							debug() const;

public:
	AStar(Node *start, Node const &goal, IHeuristic const &h);
	virtual ~AStar();

	void							run();
	
	static int				getSize();
//	std::list<Node*>	getPath() const;
	
//	static void				erase(Node *el);
//	static void				erase_pair(std::pair<std::vector<int>, Node *> el);

	class NoSolution: public std::exception{
		public:
			NoSolution() throw();
			~NoSolution() throw();
			virtual const char *what() const throw();
	};

};


std::ostream	&operator<<(std::ostream &o, AStar const &c);

#endif

