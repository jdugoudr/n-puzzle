/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Puzzle.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:18:18 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/08 22:09:27 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PUZZLE_HPP
# define PUZZLE_HPP

#include "IHeuristic.hpp"
#include "Node.hpp"

#include <iostream>
#include <string>
#include <list>
#include <map>

class Puzzle{

private:
	IHeuristic								*_heuristic;
	Node									*_startNode;
	Node									*_endNode;
	int										_mapSize;
	std::list<Node *>							_openList;
	std::list<Node *>						_closedList;
	//int									_solvable;
	int										_numberOfStates;	// complexity in size
	int										_numberOfMoves;

public:
	Puzzle(IHeuristic *heuristic);
	virtual ~Puzzle();

	IHeuristic const		*getHeuristic() const;
	Node const				*getStartNode() const;
	Node const				*getEndNode() const;
	int						getMapSize() const;
	std::list<Node *>		getOpenList() const;
	std::list<Node *>		getClosedList() const;
	int						getNumberOfStates() const;
	int						getNumberOfMoves() const;

	void					setStartNode(Node *node);
	void					setEndNode(Node *node);
	void					setMapSize(int size);
	void					setOpenList(std::list<Node *> open_list);
	void					setClosedList(std::list<Node *> closed_list);
	void					setNumberOfStates(int nb);
	void					setNumberOfMoves(int nb);
};

#endif
