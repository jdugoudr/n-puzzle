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

static std::vector<std::vector<int>>			vec_to_tdvec(std::vector<int> const &map, int size, int columns_to_lines)
{
	std::vector<std::vector<int>>		lines;

	for (int i = 0; i < size * size;)
	{
		std::vector<int> sub;
		for (int j = 0; j < size; j++)
		{
			sub.push_back(map[i]);
			i++;
		}
		lines.push_back(sub);
	}
	if (columns_to_lines)
	{
		std::vector<std::vector<int>>		cols;

		for (int i = 0; i < size; i++)
		{
			std::vector<int> sub;
			for (int j = 0; j < size; j++)
				sub.push_back(lines[j][i]);
			cols.push_back(sub);
		}

		return cols;
	}

	return lines;
}

/*
 * Search [line] for conflicts with tile [line[x]].
 * Save the indexes of all tiles in conflict with tile [line[x]].
 * If no conflicts found, return empty vector.
 */
static std::vector<int>		tile_conflicts(std::vector<int> const &line, int x, std::vector<int> const &goal, int size, int debug)
{
	std::vector<int>	conflicts;

	auto it = std::find(goal.begin(), goal.end(), line[x]);
	if (line[x] == 0 || line[x] == goal[x] || it == goal.end()) // if tile == 0 or tile is at its goal place or goal tile isn't on the same line
	{
		//std::cout << "no conflicts for " << line[x] << std::endl;	
		return (conflicts);
	}
	int goal_x = it - goal.begin();
	//std::cout << "goal for " << line[x] << " is on same line, index " << goal_x << std::endl;	

	//for (int k = x + 1; k < size; k++) // for each other tile further on the line
	for (int k = 0; k < size; k++) // for each other tile
	{
		auto it = std::find(goal.begin(), goal.end(), line[k]);
		if (k == x || line[k] == 0 || line[k] == goal[k] || it == goal.end())
			continue ;
		int goal_k = it - goal.begin();
		if ((x < k && goal_x > goal_k) || (x > k && goal_x < goal_k))
		{
			if (debug)
				std::cout << "CONFLICT between " << line[x] << " and " << line[k] << std::endl;	
			conflicts.push_back(k);
		}
	}
	return (conflicts);
}

static int		get_most_conflicts(std::vector<std::vector<int>> &vec, int size)
{
	int				i = 0;
	unsigned long	most_conflicts = 0;

	while (i < size)
	{
		if (vec[i].size() > vec[most_conflicts].size())
			most_conflicts = i;
		i++;
	}
	if (most_conflicts == 0 && vec[0].size() == 0)
		return (-1);
	return most_conflicts;
}

/*
 * Count the total conflicts in an optimal way:
 * treat the tiles with most conflicts first
 */
static int		treat_conflicts(std::vector<std::vector<int>> line_conflicts, int size)
{
	int		conflicts = 0;

	/*for (auto &line: line_conflicts)
	{
		if (line.size() > 0)
		{
			for (auto &col: line)
			{
				std::cout << col << " ";	
			}
		}
		std::cout << std::endl;	
	}*/

	int		most_conflicts;

	while ((most_conflicts = get_most_conflicts(line_conflicts, size)) != -1)
	{
		//std::cout << "most conflicts is index " << most_conflicts << std::endl;	
		//for (auto &it: line_conflicts[most_conflicts])
		for (unsigned int i = 0; i < line_conflicts[most_conflicts].size(); i++)
		{
			int delete_at = line_conflicts[most_conflicts][i];
			//std::cout << "delete " << most_conflicts << " at " << delete_at << std::endl;	
			line_conflicts[delete_at].erase(std::remove(line_conflicts[delete_at].begin(), line_conflicts[delete_at].end(), most_conflicts));
			//for (auto &it: line_conflicts[delete_at])
			//	std::cout << it << std::endl;
		}
		line_conflicts[most_conflicts].clear();

		conflicts++;
	}

	/*for (auto &line: line_conflicts)
	{
		if (line.size() > 0)
		{
			for (auto &col: line)
			{
				std::cout << col << " ";	
			}
		}
		std::cout << std::endl;	
	}*/



	return conflicts;
}


/*
 * This heuristic is an improved version of the Manhattan heuristic.
 * It adds, to the cost of path-to-goal of each tile (Manhattan Distance), the cost of
 * conflict resolutions that may appear on that path.
 *
 * For each line and column of the goal map, we look for tiles in conflict.
 * We add a cost of 2 for each conflicting pair.
 *
 * Two tiles A and B are in linear conflict if :
 * - they are on the same line/column
 * - their goal positions also are on this line/column
 * - A is to the right of B, and the goal position of A is to the left of the goal
 * position of B. (replace left/right with up/down in the case of a column)
 *
 * When 3 or more tiles are in linear conflict, we pick the tile involved in
 * the most conflicts to move first. This way we can minimize the number of
 * additional moves, and the heuristic is optimistic and thus admissible.
*/

int		LinearConflicts::calculate(std::vector<int> const &map, Node const &goal_node) const
{
	//std::cout << "LINEAR CONFLICTS" << std::endl;	
	int	manhattan_cost = 0;
	int	conflicts_cost = 0;
	int	size = goal_node._mapSize;

	manhattan_cost = _manhattan->calculate(map, goal_node);

	std::vector<std::vector<int>> lines_state = vec_to_tdvec(map, size, 0);
	std::vector<std::vector<int>> lines_goal = vec_to_tdvec(goal_node._map, size, 0);

	conflicts_cost = 0;
	for (int y = 0; y < size; y++)
	{
		std::vector<std::vector<int>>	line_conflicts;
		for (int x = 0; x < size; x++)
			line_conflicts.push_back(tile_conflicts(lines_state[y], x, lines_goal[y], size, 0));
		conflicts_cost += treat_conflicts(line_conflicts, size);
	}
	//std::cout << "conflicts after lines = " << conflicts_cost << std::endl;	


	// PAREIL POUR COLONNES
	std::vector<std::vector<int>> columns_state = vec_to_tdvec(map, size, 1);
	std::vector<std::vector<int>> columns_goal = vec_to_tdvec(goal_node._map, size, 1);

	for (int y = 0; y < size; y++)
	{
		std::vector<std::vector<int>>	column_conflicts;
		for (int x = 0; x < size; x++)
			column_conflicts.push_back(tile_conflicts(columns_state[y], x, columns_goal[y], size, 0));
		conflicts_cost += treat_conflicts(column_conflicts, size);
	}
	//std::cout << "conflicts after columns = " << conflicts_cost << std::endl;	






	// ne marche peut-etre pas avec une resolution en snail ?
	return (manhattan_cost + (conflicts_cost * 2));
}

std::string	const	LinearConflicts::getName() const
{
	return _name;
}
