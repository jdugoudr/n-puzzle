/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 17:23:09 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/10 16:25:38 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AStar.hpp"
#include "Node.hpp"
#include "Case.hpp"
#include "IHeuristic.hpp"
#include "Manhattan.hpp"
#include <array>
#include <iostream>
#include <exception>

using namespace std;

int main( void )
{
	Case	a(1, 0, 0);
	Case	b(2, 1, 0);
	Case	c(3, 0, 1);
	Case	d(0, 1, 1);

	array<Case *, 2>	l1 = {&c, &a};
	array<Case *, 2>	l2 = {&b, &d};

	array<Case *, 2>	l3 = {&a, &c};
	array<Case *, 2>	l4 = {&b, &d};

	array<array<Case *, 2>, 2>	map = {l1, l2};
	array<array<Case *, 2>, 2>	map2 = {l3, l4};

	Node	n(map);
	Node	n2(map2);

	IHeuristic	*h = new Manhattan();

	AStar	star(n, n2, *h);

//	std::cout << star;

	try {
		star.run();
	} catch (std::exception &e){
		std::cerr << e.what() << std::endl;
	}

	delete h;

	return 0;
}
