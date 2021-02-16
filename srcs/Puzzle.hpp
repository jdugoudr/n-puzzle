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

# include "IHeuristic.hpp"
# include "Manhattan.hpp"
# include "Node.hpp"

# include <iostream>
# include <fstream>
# include <sstream>
# include <algorithm>
# include <string>
# include <list>
# include <map>

# define MAP_MIN_SIZE	3
# define MAP_MAX_SIZE	100

class Puzzle{

private:
	IHeuristic				*_heuristic;
	Node					*_startNode;
	Node					*_endNode;
	int						_mapSize;
	int						_numberOfStates;	// complexity in size (memory)
	int						_numberOfMoves;		// complexity in time

	std::string				_filename;
	bool					_solvabilityCheck;	// option -n => don't check puzzle solvability
	bool					_mustBeSolvable;	// option -u => generate unsolvable map 

	Node					*generate_start_node(int size);
	Node					*get_start_node_from_file(std::string filename);
	int						count_inversions(std::vector<int> const &map, int size) const;
	int						check_validity(std::vector<int> map, const int size);
	std::vector<int>		parse_file(std::string filename, unsigned long &size);
	std::vector<int>		split_stoi(std::string line);
	std::vector<int>		generate_resolved_array(int size);


public:
	Puzzle();
	virtual ~Puzzle();

	IHeuristic const		*getHeuristic() const;
	Node const				*getStartNode() const;
	Node const				*getEndNode() const;
	int						getMapSize() const;
	std::list<Node *>		getOpenList() const;
	std::list<Node *>		getClosedList() const;
	int						getNumberOfStates() const;
	int						getNumberOfMoves() const;

	std::string				getFilename() const;
	bool					getSolvabilityCheck() const;
	bool					getMustBeSolvable() const;

	void					setHeuristic(std::string heuristic_name);
	void					setMapSize(int size);
	void					setOpenList(std::list<Node *> open_list);
	void					setClosedList(std::list<Node *> closed_list);
	void					setNumberOfStates(int nb);
	void					setNumberOfMoves(int nb);
	void					setFilename(std::string filename);
	void					setSolvabilityCheck(bool state);
	void					setMustBeSolvable(bool state);

	void					create_start_node();
	void					create_end_node();
	bool					is_solvable(void) const;
};

#endif
