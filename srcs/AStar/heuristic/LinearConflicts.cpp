/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LinearConflicts.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:51:28 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/16 22:57:55 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * This heuristic is an improved version of the Manhattan heuristic.
 * It adds, to the Manhattan Distance cost of each tile, the cost of
 * conflict resolutions that may appear on that path.
 *
 * For each line and column of the goal map, we look for tiles in conflict.
 * We add a cost of 2 for each conflicting pair.
 *
 * Two tiles A and B are in linear conflict if :
 * - they are on the same line
 * - their goal positions also are on this line
 * - A is to the right of B, and the goal position of A is to the left of the goal
 * position of B.
 *
 * When 3 or more tiles are in linear conflict, we pick the tile involved in
 * the most conflicts to move first. This way we can minimize the number of
 * additional moves, and the heuristic stays optimistic and admissible.
*/

#include "LinearConflicts.hpp"
#include "Manhattan.hpp"
#include <vector>
#include <algorithm>

LinearConflicts::LinearConflicts():
	_name("LinearConflicts")
{
	_manhattan = new Manhattan();
}

LinearConflicts::~LinearConflicts()
{
	delete _manhattan;
}

std::vector<std::vector<int>>		LinearConflicts::vec_to_2dvec(std::vector<int> const &map, int size, bool columns_to_lines) const
{
	std::vector<std::vector<int>>		lines;

	int i = 0;
	while (i < size * size)
	{
		std::vector<int> line;
		for (int j = 0; j < size; j++)
		{
			line.push_back(map[i]);
			i++;
		}
		lines.push_back(line);
	}

	if (columns_to_lines)
	{
		std::vector<std::vector<int>>		columns;

		for (int i = 0; i < size; i++)
		{
			std::vector<int> col;
			for (int j = 0; j < size; j++)
				col.push_back(lines[j][i]);
			columns.push_back(col);
		}
		return columns;
	}

	return lines;
}

/*
 * Search [state_line] for conflicts between tile [state_line[a]] and the other tiles.
 * Save the indexes of all conflicting tiles in a vector.
 * If no conflicts found, return empty vector.
 */
std::vector<int>		LinearConflicts::get_tile_conflicts(std::vector<int> const &state_line, size_t a, std::vector<int> const &goal_line) const
{
	size_t				goal_a;
	size_t				b;
	size_t				goal_b;
	std::vector<int>	conflicts;

	auto it = std::find(goal_line.begin(), goal_line.end(), state_line[a]);
	if (state_line[a] == 0 || state_line[a] == goal_line[a] || it == goal_line.end())
		return (conflicts);

	goal_a = it - goal_line.begin();

	for (b = 0; b < state_line.size(); b++)
	{
		auto it = std::find(goal_line.begin(), goal_line.end(), state_line[b]);
		if (b == a || state_line[b] == 0 || state_line[b] == goal_line[b] || it == goal_line.end())
			continue ;

		goal_b = it - goal_line.begin();
		if ((a < b && goal_a > goal_b) || (a > b && goal_a < goal_b))
			conflicts.push_back(b);
	}
	return (conflicts);
}

int		LinearConflicts::get_most_conflicted_tile(std::vector<std::vector<int>> &vec, int size) const
{
	size_t	most_conflicts = 0;

	for (int i = 0; i < size; i++)
	{
		if (vec[i].size() > vec[most_conflicts].size())
			most_conflicts = i;
	}
	if (most_conflicts == 0 && vec[0].size() == 0)
		return (-1);
	return most_conflicts;
}

/*
 * Treat tiles with most conflicts first
 */
int		LinearConflicts::treat_conflicts(std::vector<std::vector<int>> &line_conflicts, int size) const
{
	int					conflicts = 0;
	int					tile;
	int					to_delete;
	std::vector<int>	*tmp;

	while ((tile = this->get_most_conflicted_tile(line_conflicts, size)) != -1)
	{
		for (size_t i = 0; i < line_conflicts[tile].size(); i++)
		{
			to_delete = line_conflicts[tile][i];
			tmp = &line_conflicts[to_delete];
			tmp->erase(std::remove(tmp->begin(), tmp->end(), tile));
		}

		line_conflicts[tile].clear();
		conflicts++;
	}
	return conflicts;
}

int		LinearConflicts::count_conflicts(std::vector<int> const &map,
		std::vector<int> const &goal_map, int size, bool columns_to_lines) const
{
	int								cost = 0;
	std::vector<std::vector<int>>	state;
	std::vector<std::vector<int>>	goal;
	std::vector<std::vector<int>>	conflicts;

	state = this->vec_to_2dvec(map, size, columns_to_lines);
	goal = this->vec_to_2dvec(goal_map, size, columns_to_lines);

	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
			conflicts.push_back(this->get_tile_conflicts(state[y], x, goal[y]));
		cost += this->treat_conflicts(conflicts, size);
		conflicts.clear();
	}
	return cost;
}

/*
 * Counts Manhattan Distance cost, then count conflicts in lines and columns.
 * Total conflicts number is multiplied by 2: a conflicting tile needs 2 moves to 
 * move out of the line and back again.
 */
int		LinearConflicts::calculate(std::vector<int> const &map, Node const &goal_node) const
{
	int	manhattan_cost;
	int	conflicts_cost = 0;

	manhattan_cost = this->_manhattan->calculate(map, goal_node);

	conflicts_cost += this->count_conflicts(map, goal_node._map, goal_node._mapSize, 0); 
	conflicts_cost += this->count_conflicts(map, goal_node._map, goal_node._mapSize, 1); 

	return (manhattan_cost + (2 * conflicts_cost));
}

std::string	const	LinearConflicts::getName() const
{
	return _name;
}
