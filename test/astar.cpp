/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 17:23:09 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/12 22:42:07 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AStar.hpp"
#include "Node.hpp"
//#include "Case.hpp"
#include "IHeuristic.hpp"
#include "Manhattan.hpp"
#include <array>
#include <iostream>
#include <exception>

using namespace std;

int main( void )
{
//		vector<int> map = {3,0,2,1};
//		vector<int> goal = {1,2,0,3};
//
//		Node	n(map, 2);
//		Node	n2(goal, 2);





	vector<int>	map = {0,2,3,1,4,5,8,7,6};
	vector<int>	goal = {1,2,3,8,0,4,7,6,5};

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
