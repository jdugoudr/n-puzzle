/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Hamming.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:51:28 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/16 22:57:55 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Hamming.hpp"
#include <vector>

Hamming::Hamming():
	_name("Hamming")
{
}

Hamming::~Hamming()
{
}

/*
 * Comparing the current map and the goal map,
 * we count the total number of tiles which
 * are not in their correct position.
*/
int		Hamming::calculate(std::vector<int> const &map, Node const &goal) const
{
	int	cost = 0;
	int	size = goal._mapSize;

	std::vector<int> gmap = goal._map;

	for (int pos = 0 ; pos < size * size ; pos++)
	{
		if (map[pos] == 0)
			continue ;
		if (map[pos] != gmap[pos])
			cost += 1;
	}

	return cost;
}

std::string	const	Hamming::getName() const
{
	return _name;
}
