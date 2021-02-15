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
#include <unistd.h>	// for getopt()

using namespace std;

static int				usage(int ret)
{
	std::cout << std::endl;	
	std::cout << "usage: " << std::endl;
	std::cout << "   n-puzzle -h                 - print this help" << std::endl;
	std::cout << "   n-puzzle -g [size]          - generate a solvable random puzzle with given size" << std::endl;
	std::cout << "                      -u       - randomly generated puzzle must be unsolvable (optionnal)" << std::endl;
	std::cout << "   n-puzzle -f [file]          - use puzzle from file" << std::endl;
	std::cout << "                      -n       - do not check if puzzle is solvable (optionnal)" << std::endl;
	std::cout << std::endl;	

	std::cout << "Input file format:" << std::endl;
	std::cout << "                3     #size. must be between 3 and 100" << std::endl;
	std::cout << "                3 2 6" << std::endl;
	std::cout << "                1 4 0" << std::endl;
	std::cout << "                8 7 5" << std::endl;

	return (ret);
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

static void				parse_arguments(int ac, char **av, Puzzle *puzzle)
{
    int 			opt;

	if (ac == 1)
	{
		delete puzzle;
		exit (usage(0));
	}

    while ((opt = getopt(ac, av, "hf:g:un")) != -1)
	{
        switch (opt)
        {
            case 'h':
			{
				delete puzzle;
				exit (usage(0));
			}
            case 'f':
			{
				if (puzzle->getMapSize())
					throw (invalid_argument("You must choose between reading from a file and generating a puzzle"));
				if (std::string(optarg).empty())
					throw (invalid_argument("Wrong or missing argument"));
				puzzle->setFilename(optarg);
				break;
			}
            case 'g':
			{
				if (!puzzle->getFilename().empty())
					throw (invalid_argument("You must choose between reading from a file and generating a puzzle"));
				puzzle->setMapSize(atoi(optarg));
				break;
			}
            case 'u':
			{
				if (!puzzle->getFilename().empty())
					throw (invalid_argument("Incompatible arguments"));
				puzzle->setMustBeSolvable(0);
				puzzle->setSolvabilityCheck(0);
				break;
			}
            case 'n':
			{
				if (puzzle->getMapSize())
					throw (invalid_argument("Incompatible arguments"));
				puzzle->setSolvabilityCheck(0);
				break;
			}
			case '?':
				throw (invalid_argument("Wrong or missing argument"));
        }
	}

	if (optind < ac)
		throw (invalid_argument("Wrong argument"));
	else if (puzzle->getFilename().empty() && !puzzle->getMapSize())
		throw (invalid_argument("You must specify a puzzle size"));
	else if (puzzle->getMapSize() < MAP_MIN_SIZE || puzzle->getMapSize() > MAP_MAX_SIZE)
		throw (invalid_argument("Wrong puzzle size"));
}

int						main(int ac, char **av)
{
	Puzzle			*puzzle = new Puzzle();
	Node			*start_node;
	std::string		heuristic_name;

	try {
		parse_arguments(ac, av, puzzle);
	} catch (exception &e) {
		cout << "Exception: " << e.what() << endl;
		return (usage(1));
	}

	if ((heuristic_name = choose_heuristic()).empty())
	{
		delete puzzle;
		return (usage(1));
	}
	puzzle->setHeuristic(heuristic_name);

	// mettre dans puzzle
	if (puzzle->getFilename().empty())
		start_node = generate_start_node(puzzle);
	else
		start_node = get_node_from_file(puzzle->getFilename());

	if (start_node == NULL)
	{
		delete puzzle;
		return (1);
	}

	puzzle->setStartNode(start_node);
	puzzle->setMapSize(start_node->getMapSize());

	std::cout << "START NODE:" << std::endl;
	std::cout << *(puzzle->getStartNode()) << std::endl;

	puzzle->setEndNode(create_end_node(puzzle->getMapSize()));
	std::cout << "END NODE:" << std::endl;
	std::cout << *(puzzle->getEndNode()) << std::endl;

	if (puzzle->getSolvabilityCheck() && !puzzle->isSolvable())
	{
		std::cout << "This puzzle is not solvable." << std::endl;
		delete puzzle;
		return(0);
	}


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
	return (0);
}
