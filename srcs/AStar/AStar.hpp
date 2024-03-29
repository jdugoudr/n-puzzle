/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AStar.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:12:59 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/24 21:20:44 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	ASTAR_HPP
# define ASTAR_HPP

#include "Node.hpp"
#include "pq_custom.hpp"
#include "IHeuristic.hpp"
#include <list>
//#include <queue>
#include <map>
#include <iostream>

class AStar{

private:
	static	int																		_size;
	Node const																		&_goal;
	IHeuristic const															&_h;
	Node																					*_start;
	std::vector<Node*>														_finaleResult;

	std::map<std::vector<int>, Node*>							_set;
	pq_custom<Node>																_openList;



	void					pushOpenList(Node &node);
	//void					pushFromOpenToClose(Node &m);
	void					pushFromCloseToOpen(Node &m);
	void					pushNewNodeToOpen(int const soFar, int const toReach,
																				Node &map, Node *parent);

//	std::vector<Node>		getNeighbor(Node &m);
	//void								getNeighbor(std::vector<int> const &m, std::array<Node,4> &lst, int &nb);
	void								getNeighbor(Node const &m, std::array<Node,4> &lst, int &nb);

	std::vector<Node*>	getPath(Node *);


	void							debug() const;

public:
	AStar(Node *start, Node const &goal, IHeuristic const &h);
	virtual ~AStar();

	std::vector<Node*>	run();
	
	static int					getSize();

	static int					_totalStatesSelected; // complexity in time
	static int					_maximumStatesRepresented; // complexity in size

	int							getSetSize();

	class NoSolution: public std::exception{
		public:
			NoSolution() throw();
			~NoSolution() throw();
			virtual const char *what() const throw();
	};

};


std::ostream	&operator<<(std::ostream &o, AStar const &c);

#endif

