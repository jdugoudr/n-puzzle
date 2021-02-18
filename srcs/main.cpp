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

using namespace std;

static int				usage(int ret, Puzzle *puzzle)
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

	if (puzzle != NULL)
		delete puzzle;

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
		throw (invalid_argument("Invalid number"));

	return (array[x - 1]);
}

static void				parse_arguments(int ac, char **av, Puzzle *puzzle)
{
    int 			opt = 0;
	bool			g_flag, f_flag, u_flag, n_flag;

	g_flag = f_flag = u_flag = n_flag = 0;
	if (ac == 1)
		exit (usage(0, puzzle));

    while ((opt = getopt(ac, av, "hf:g:un")) != -1)
	{
        switch (opt)
        {
            case 'h':
				exit (usage(0, puzzle));
            case 'f':
			{
				if (g_flag || u_flag)
					throw (invalid_argument("Incompatible arguments"));
				f_flag = 1;
				puzzle->setFilename(optarg);
				break;
			}
            case 'g':
			{
				if (f_flag || n_flag)
					throw (invalid_argument("Incompatible arguments"));
				g_flag = 1;
				if (std::string(optarg).find_first_not_of("0123456789") != std::string::npos)
					throw (invalid_argument("Invalid puzzle size"));
				puzzle->setMapSize(atoi(optarg));
				break;
			}
            case 'u':
			{
				if (f_flag || n_flag)
					throw (invalid_argument("Incompatible arguments"));
				u_flag = 1;
				puzzle->setMustBeSolvable(0);
				puzzle->setSolvabilityCheck(0);
				break;
			}
            case 'n':
			{
				if (g_flag || u_flag)
					throw (invalid_argument("Incompatible arguments"));
				n_flag = 1;
				puzzle->setSolvabilityCheck(0);
				break;
			}
			case '?':
				throw (invalid_argument("Wrong or missing argument"));
        }
	}

	if (optind < ac)
		throw (invalid_argument("Wrong argument"));
	else if (!f_flag && !g_flag)
		throw (invalid_argument("Missing argument"));
	else if (g_flag && (puzzle->getMapSize() < MAP_MIN_SIZE
				|| puzzle->getMapSize() > MAP_MAX_SIZE))
		throw (invalid_argument("Invalid puzzle size"));
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
		return(0);
	}

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
