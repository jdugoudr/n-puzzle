/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 19:14:19 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/12 16:49:03 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n-puzzle.hpp"
#include "Puzzle.hpp"
#include "AStar.hpp"

#include <array>
#include <iostream>

static void				usage(void)
{
	std::cout << std::endl;	
	std::cout << "usage: " << std::endl;
	std::cout << "   n-puzzle -h        - print this help" << std::endl;
	std::cout << "   n-puzzle           - generate a random puzzle" << std::endl;
	std::cout << "   n-puzzle [file]    - use puzzle from file with following format:" << std::endl;
	std::cout << std::endl;	
	std::cout << "                3     #size. must be between 3 and 100" << std::endl;
	std::cout << "                3 2 6" << std::endl;
	std::cout << "                1 4 0" << std::endl;
	std::cout << "                8 7 5" << std::endl;
}

static std::string		choose_heuristic(void)
{
	unsigned long				x = 0;
	std::array<std::string, 1>	array = {"Manhattan"};	//completer avec les autres heuristiques
	
	std::cout << std::endl;	
	std::cout << "Choose a heuristic function : [1] Manhattan" << std::endl;	
	std::cout << "Type a number : ";	
	std::cin >> x;

	if (!(x >= 1 && x <= array.size()))
	{
		std::cout << "Invalid number" << std::endl;	
		return ("");
	}

	return (array[x - 1]);
}

int	main(int ac, char **av)
{
	Puzzle			*puzzle;
	Node			*start_node;
	std::string		heuristic_name;

	if (ac > 2 || (ac > 1 && std::string(av[1]) == "-h"))
	{
		usage();
		return (0);
	}
	
	if ((heuristic_name = choose_heuristic()).empty())
		return (0);

	if (ac == 1)
		start_node = generate_start_node();
	else
		start_node = get_node_from_file(av[1]);

	if (start_node == NULL)
		return (0);

	puzzle = new Puzzle(heuristic_name);
	puzzle->setStartNode(start_node);
	puzzle->setMapSize(start_node->getMapSize());

	std::cout << "START NODE:" << std::endl;
	std::cout << *(puzzle->getStartNode()) << std::endl;

	puzzle->setEndNode(create_end_node(puzzle->getMapSize()));
	std::cout << "END NODE:" << std::endl;
	std::cout << *(puzzle->getEndNode()) << std::endl;

	// algo
	AStar	star(*puzzle->getStartNode(),
								*puzzle->getEndNode(),
								*puzzle->getHeuristic());

	try {
		star.run();
	} catch (std::exception &e){
		std::cerr << e.what() << std::endl;
	}


	delete puzzle;
	return 0;
}
