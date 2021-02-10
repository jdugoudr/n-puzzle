/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 17:23:09 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/10 22:06:04 by jdugoudr         ###   ########.fr       */
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
	Case	*a = new Case(1, 0, 0);
	Case	*b = new Case(2, 1, 0);
	Case	*c = new Case(3, 0, 1);
	Case	*d = new Case(0, 1, 1);

	vector<Case *>	l1 = {a, b};
	vector<Case *>	l2 = {d, c};

	vector<Case *>	l3 = {c, d};
	vector<Case *>	l4 = {b, a};

	vector<vector<Case *>>	map = {l1, l2};
	vector<vector<Case *>>	map2 = {l3, l4};

	Node	n(map, 2);
	Node	n2(map2, 2);

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
