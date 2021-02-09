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

void		usage()
{
	std::cout << "usage: " << std::endl;
	std::cout << "   n-puzzle -h        - print this help" << std::endl;
	std::cout << "   n-puzzle           - generate a randon puzzle" << std::endl;
	std::cout << "   n-puzzle [file]    - use puzzle from file" << std::endl;
}

int	main(int ac, char **av)
{
	std::cout << std::endl;	
	if (ac > 2 || (ac > 1 && std::string(av[1]) == "-h"))
	{
		usage();
		return (0);
	}

	std::array<std::string, 1>		array = {"Manhattan"};	//completer avec les autres heuristiques
	
	unsigned long	x = 0;
	std::cout << "Choose a heuristic function : [1] Manhattan" << std::endl;	
	std::cout << "Type a number : ";	
	std::cin >> x;
	if (!(x >= 1 && x <= array.size()))
	{
		std::cout << "Invalid number" << std::endl;	
		return (0);
	}

	Puzzle		*puzzle = new Puzzle(array[x - 1]);
	std::cout << "Created puzzle object with heuristic " << puzzle->getHeuristic()->getName() << std::endl;	

	if (ac == 1)
	{
		std::cout << "We have to generate a puzzle our self" << std::endl;
		//puzzle._startNode = generate_puzzle();
	}
	else
	{
		std::cout << "open : " << av[1] << std::endl;
		//puzzle._startNode = parse_file(av[1]);
	}

	// algo

	return 0;
}
