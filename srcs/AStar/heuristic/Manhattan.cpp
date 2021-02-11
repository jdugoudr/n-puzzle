/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manhattan.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:51:28 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/11 20:43:39 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Manhattan.hpp"
#include "Case.hpp"
#include "find_if_mix.hpp"

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

	std::vector<std::vector<Case*>> cit = current.getMap();

	for (auto git: goal.getMap())
	{
		for (auto git2: git)
		{
			for (int i = 0; i < current.getMapSize() ;i++)
			{
				auto it = find_if_mix((cit[i]).begin(), (cit[i]).end(),
										git2, Case::compare_ptr);
				if (it != (cit[i]).end())
				{
					coast += calculDiff(*(*it), *git2);
					break ;
				}
			}
		}
	}
	return coast;
}

int		Manhattan::calculDiff(Case &curr, Case &goal) const
{
	int	x1, x2, y1, y2;
	int	diff = 0;

	x1 = curr.getPosX();
	x2 = goal.getPosX();
	y1 = curr.getPosY();
	y2 = goal.getPosY();


	diff += x1 > x2 ? x1 - x2 : x2 - x1;
	diff += y1 > y2 ? y1 - y2 : y2 - y1;

	return diff;
}

std::string	const	Manhattan::getName() const
{
	return _name;
}
