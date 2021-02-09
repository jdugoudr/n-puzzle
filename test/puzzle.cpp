/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_node.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 22:07:10 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/08 22:15:39 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Manhattan.hpp"
#include "Puzzle.hpp"
#include "Node.hpp"

using namespace std;

int	main( void )
{
	IHeuristic		*heuristic = new Manhattan;

	Puzzle	puzzle(heuristic);
	cout << "Puzzle object created with heuristic " << puzzle.getHeuristic()->getName() << endl;	

	puzzle.setMapSize(4);
	cout << "Map size = " << puzzle.getMapSize() << endl;

	const IHeuristic		*tmp = puzzle.getHeuristic();
	cout << "Test " << tmp->getName() << endl;	

	delete heuristic;
	return 0;
}
