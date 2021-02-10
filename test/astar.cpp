/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 17:23:09 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/10 22:27:44 by jdugoudr         ###   ########.fr       */
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
	//Case	*a = new Case(1, 0, 0);
	//Case	*b = new Case(2, 1, 0);
	//Case	*c = new Case(3, 0, 1);
	//Case	*d = new Case(0, 1, 1);

//	vector<Case *>	l1 = {a, b};
//	vector<Case *>	l2 = {d, c};
//
//	vector<Case *>	l3 = {c, d};
//	vector<Case *>	l4 = {b, a};



	Case	*a0 = new Case(7, 0, 0);
	Case	*b0 = new Case(2, 1, 0);
	Case	*c0 = new Case(4, 2, 0);
	Case	*a1 = new Case(8, 1, 0);
	Case	*b1 = new Case(5, 1, 1);
	Case	*c1 = new Case(1, 1, 2);
	Case	*a2 = new Case(0, 2, 0);
	Case	*b2 = new Case(6, 2, 1);
	Case	*c2 = new Case(3, 2, 2);

	vector<Case *>	l0 = {a0, b0, c0};
	vector<Case *>	l1 = {a1, b1, c1};
	vector<Case *>	l2 = {a2, b2, c2};

	Case	*ag0 = new Case(1, 0, 0);
	Case	*bg0 = new Case(8, 1, 0);
	Case	*cg0 = new Case(7, 2, 0);
	Case	*ag1 = new Case(2, 1, 0);
	Case	*bg1 = new Case(0, 1, 1);
	Case	*cg1 = new Case(6, 1, 2);
	Case	*ag2 = new Case(3, 2, 0);
	Case	*bg2 = new Case(4, 2, 1);
	Case	*cg2 = new Case(5, 2, 2);

	vector<Case *>	lg0 = {ag0, bg0, cg0};
	vector<Case *>	lg1 = {ag1, bg1, cg1};
	vector<Case *>	lg2 = {ag2, bg2, cg2};

	vector<vector<Case *>>	map = {l0, l1, l2};
	vector<vector<Case *>>	goal = {lg0, lg1, lg2};

	Node	n(map, 3);
	Node	n2(goal, 3);

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
