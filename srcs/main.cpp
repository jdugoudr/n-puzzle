/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 19:14:19 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/08 21:07:34 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n-puzzle.hpp"
#include "Puzzle.hpp"

#include <array>
#include <iostream>

static void				usage(void)
{
	std::cout << "usage: " << std::endl;
	std::cout << "   n-puzzle -h        - print this help" << std::endl;
	std::cout << "   n-puzzle           - generate a randon puzzle" << std::endl;
	std::cout << "   n-puzzle [file]    - use puzzle from file with following format:" << std::endl;
	std::cout << std::endl;	
	std::cout << "                3 #size must be between 3 and 100" << std::endl;
	std::cout << "                3 2 6" << std::endl;
	std::cout << "                1 4 0" << std::endl;
	std::cout << "                8 7 5" << std::endl;
}

static std::string		choose_heuristic(void)
{
	unsigned long				x = 0;
	std::array<std::string, 1>	array = {"Manhattan"};	//completer avec les autres heuristiques
	
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
	std::cout << std::endl;	
	if (ac > 2 || (ac > 1 && std::string(av[1]) == "-h"))
	{
		usage();
		return (0);
	}

	std::string		heuristic_name;
	
	if ((heuristic_name = choose_heuristic()).empty())
		return (0);

	std::cout << std::endl;	

	Puzzle		*puzzle = new Puzzle(heuristic_name);
	std::cout << "Created puzzle object with heuristic " << puzzle->getHeuristic()->getName() << std::endl;	

	Node		*start_node;
	if (ac == 1)
	{
		std::cout << "We have to generate a puzzle ourselves" << std::endl;
		start_node = generate_puzzle();
	}
	else
		start_node = get_node_from_file(av[1]);

	if (start_node == NULL)
	{
		delete puzzle;
		return (0);
	}
	puzzle->setStartNode(start_node);
	puzzle->setMapSize(start_node->getMapSize());

	std::cout << "START NODE:" << std::endl;
	std::cout << *(puzzle->getStartNode()) << std::endl;


	// check if solvable

	// create end_node
	puzzle->setEndNode(create_end_node(puzzle->getMapSize()));
	std::cout << "END NODE:" << std::endl;
	std::cout << *(puzzle->getEndNode()) << std::endl;

	// algo

	delete puzzle;
	return 0;
}
