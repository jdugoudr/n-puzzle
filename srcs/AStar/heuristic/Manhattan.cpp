/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manhattan.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:51:28 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/15 16:39:25 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Manhattan.hpp"

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
int		Manhattan::calculate(Node const &current, Node const &goal) const
{
	int	coast = 0;
	int	size = goal.getMapSize();

	std::vector<int> map = current.getMap();
	std::vector<int> gmap = goal.getMap();

	for (int pos = 0 ;
					pos < size * size ;
					pos++)
	{
		if (map[pos] == 0)
			continue ;
		for (int gpos = 0 ;
						gpos < size * size ;
						gpos++)
		{
			if (map[pos] == gmap[gpos])
			{
				int valAbsolute = pos > gpos ? pos-gpos : gpos-pos;
				coast += valAbsolute / size + valAbsolute % size;
//				std::cout << "Pour : " << map[pos] 
//									<< " Abs : " << valAbsolute 
//									<< " div : " << valAbsolute / size 
//									<< " modulo : " << valAbsolute % size
//									<< " distance : "
//									<< valAbsolute / size + valAbsolute % size
//									<< std::endl;
				break ;
			}
		}
	}
	return coast;
}

//int		Manhattan::calculDiff(int curr, int goal) const
//{
//	return curr > goal ? curr - goal : goal - curr;
//}

std::string	const	Manhattan::getName() const
{
	return _name;
}
