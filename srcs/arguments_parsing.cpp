/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_parsing.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 22:51:42 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/25 22:51:44 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n-puzzle.hpp"

std::string			choose_heuristic(void)
{
	unsigned long				x = 0;
	std::array<std::string, 3>	array = {"Manhattan", "Hamming", "LinearConflicts"};

	std::cout << "Choose a heuristic function : [1] Manhattan  [2] Hamming  [3] Linear Conflicts" << std::endl;
	std::cout << "Type a number : ";
	std::cin >> x;
	std::cout << std::endl;

	if (!(x >= 1 && x <= array.size()))
		throw (std::invalid_argument("Invalid heuristic number"));

	return (array[x - 1]);
}

void				parse_arguments(int ac, char **av, Puzzle *puzzle)
{
    int 			opt = 0;
	bool			g_flag, f_flag, u_flag;

	g_flag = f_flag = u_flag = 0;
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
					throw (std::invalid_argument("Incompatible arguments"));
				f_flag = 1;
				puzzle->setFilename(optarg);
				break;
			}
            case 'g':
			{
				if (f_flag)
					throw (std::invalid_argument("Incompatible arguments"));
				g_flag = 1;
				if (std::string(optarg).find_first_not_of("0123456789") != std::string::npos)
					throw (std::invalid_argument("Invalid puzzle size"));
				puzzle->setMapSize(atoi(optarg));
				break;
			}
            case 'u':
			{
				if (f_flag)
					throw (std::invalid_argument("Incompatible arguments"));
				u_flag = 1;
				puzzle->setMustBeSolvable(0);
				break;
			}
            case 'n':
			{
				puzzle->setSolvabilityCheck(0);
				break;
			}
			case '?':
				throw (std::invalid_argument("Wrong or missing argument"));
        }
	}

	if (optind < ac)
		throw (std::invalid_argument("Wrong argument"));
	else if (!f_flag && !g_flag)
		throw (std::invalid_argument("Missing argument"));
	else if (g_flag && (puzzle->getMapSize() < MAP_MIN_SIZE
				|| puzzle->getMapSize() > MAP_MAX_SIZE))
		throw (std::invalid_argument("Invalid puzzle size"));
}
