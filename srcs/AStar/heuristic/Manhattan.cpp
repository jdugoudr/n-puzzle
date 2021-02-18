/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manhattan.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:51:28 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/16 22:57:55 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Manhattan.hpp"
#include <vector>

Manhattan::Manhattan():
	_name("Manhattan")
{
}

Manhattan::~Manhattan()
{
}

/*
 * For each element of map goal
 * We look for the iterator of his corresponding value into
 * 	current node.
 *
 * Then we calculate the disctance between the two point
*/
int		Manhattan::calculate(std::vector<int> const &map, Node const &goal) const
{
	int	coast = 0;
	int	size = goal._mapSize;

	std::vector<int> gmap = goal._map;

	for (int pos = 0 ; pos < size * size ; pos++)
	{
		if (map[pos] == 0)
			continue ;
		for (int gpos = 0 ; gpos < size * size ; gpos++)
		{
			if (map[pos] == gmap[gpos])
			{
				int valAbsolute = pos > gpos ? pos-gpos : gpos-pos;
				coast += valAbsolute / size + valAbsolute % size;
				break ;
			}
		}
	}

	return coast;
}

std::string	const	Manhattan::getName() const
{
	return _name;
}
