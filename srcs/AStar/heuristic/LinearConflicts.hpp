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
	std::string				_name;
	IHeuristic				*_manhattan;

public:
	LinearConflicts();
	virtual ~LinearConflicts();

	virtual int					calculate(std::vector<int> const &map, Node const &goal) const;
	virtual std::string const	getName() const;
};

#endif

