/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 19:14:19 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/25 23:42:17 by jd               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n-puzzle.hpp"
#include "Puzzle.hpp"
#include "AStar.hpp"

using namespace std;

int					usage(int ret, Puzzle *puzzle)
{
	std::cout << "n-puzzle options: " << std::endl;
	std::cout << "   -h              - print this help" << std::endl;
	std::cout << "   -g [size]       - generate a solvable random puzzle with given size" << std::endl;
	std::cout << "   -u              - randomly generated puzzle must be unsolvable (optionnal)" << std::endl;
	std::cout << "   -f [file]       - use puzzle from file" << std::endl;
	std::cout << "   -n              - do not check if puzzle is solvable (optionnal)" << std::endl << std::endl;

	std::cout << "Input file format:" << std::endl;
	std::cout << "                3     #map size. must be between 3 and 100" << std::endl;
	std::cout << "                3 2 6" << std::endl;
	std::cout << "                1 4 0" << std::endl;
	std::cout << "                8 7 5" << std::endl;

	if (puzzle != NULL)
		delete puzzle;

	return (ret);
}

int						main(int ac, char **av)
{
	Puzzle			*puzzle = new Puzzle();

	try
	{
		parse_arguments(ac, av, puzzle);
		puzzle->setHeuristic(choose_heuristic());
	}
	catch (exception &e)
	{
		std::cerr << "Invalid argument exception: " << e.what() << std::endl;
		return (usage(1, puzzle));
	}

	puzzle->create_start_end_nodes();
	if (puzzle->getStartNode() == NULL)
	{
		delete puzzle;
		return (1);
	}

	std::cout << "START NODE:" << std::endl;
	std::cout << *(puzzle->getStartNode()) << std::endl;
	std::cout << "END NODE:" << std::endl;
	std::cout << *(puzzle->getEndNode()) << std::endl;

	if (puzzle->getSolvabilityCheck() && !puzzle->is_solvable())
	{
		std::cout << "This puzzle is not solvable." << std::endl;
		delete puzzle;
		return (0);
	}

	AStar	star(puzzle->getStartNode(),
								*puzzle->getEndNode(),
								*puzzle->getHeuristic());

	try {
		std::vector<Node*> res = star.run();
		std::cout << "Total states selected (complexity in time) : " << star._totalStatesSelected << std::endl;
		std::cout << "Maximum states represented (complexity in size) : " << star.getSetSize() << std::endl;
		std::cout << "Number of moves : " << res.size()-1 << std::endl;
		for (auto n: res)
		{
			std::cout << "( ";
			for (auto el: n->_map)
				std::cout << el << " ";
			std::cout << ")" << std::endl;
		}
	//	for (auto n: res)
	//	{
	//		std::cout << *n << " ";
	//		std::cout << "==================" << std::endl;
	//	}
	} catch (std::exception &e){
		std::cout << e.what() << std::endl;
	}

	delete puzzle;
	return (0);
}
