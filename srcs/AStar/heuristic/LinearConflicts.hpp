/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LinearConflicts.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:48:15 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/16 22:58:07 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	LINEAR_CONFLICTS_HPP
# define LINEAR_CONFLICTS_HPP

# include "IHeuristic.hpp"

# include <string>
# include <vector>

class LinearConflicts : public IHeuristic{

private:
	std::string						_name;
	IHeuristic						*_manhattan;

	std::vector<std::vector<int>>	create_2d_vector(std::vector<int> const &map, int size, bool columns_to_lines) const;
	int								count_conflicts(std::vector<int> const &map, std::vector<int> const &goal_map, int size, bool columns_to_lines) const;
	int								treat_conflicts(std::vector<std::vector<int>> &line_conflicts, int size) const;
	int								get_most_conflicted_tile(std::vector<std::vector<int>> &vec, int size) const;
	std::vector<int>				get_tile_conflicts(std::vector<int> const &state_line, size_t a, std::vector<int> const &goal_line) const;

public:
	LinearConflicts();
	virtual ~LinearConflicts();

	virtual std::string const		getName() const;

	virtual int						calculate(std::vector<int> const &map, Node const &goal) const;
	std::vector<std::vector<int>>	create_2d_vector(std::vector<int> const &map, int size, bool columns);

};

#endif

