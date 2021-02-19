/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Puzzle.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:18:18 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/16 22:52:42 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PUZZLE_HPP
# define PUZZLE_HPP

# include "IHeuristic.hpp"
# include "Manhattan.hpp"
# include "Hamming.hpp"
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

	std::string				_filename;
	bool					_solvabilityCheck;	// if option -n => don't check puzzle solvability
	bool					_mustBeSolvable;	// if option -u => generate unsolvable map 

	Node					*generate_random_start_node(Node *endNode, int solvable);
	Node					*get_start_node_from_file(std::string filename);
	int						count_inversions(std::vector<int> const &map, int size) const;
	void					check_validity(std::vector<int> map, const int size);
	std::vector<int>		parse_file(std::string filename, unsigned long &size);
	std::vector<int>		split_stoi(std::string line);
	std::vector<int>		generate_resolved_array(int size);
	int						find_empty_index(std::vector<int> const &map);


public:
	Puzzle();
	virtual ~Puzzle();

	IHeuristic const		*getHeuristic() const;
	Node 					*getStartNode() const;
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

	void					create_start_end_nodes();
	Node					*create_end_node(int size);
	bool					is_solvable(void) const;
};

#endif
