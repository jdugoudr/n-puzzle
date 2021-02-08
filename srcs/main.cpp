/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 19:14:19 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/08 19:34:33 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n-puzzle.hpp"
#include <iostream>

int	main(int ac, char **av)
{
	if (ac > 2)
		std::cout << "n-puzzle [argument]" << std::endl;
	else if (ac == 1)
		std::cout << "We have to generate a puzzle our self" << std::endl;
	else
		std::cout << "open : " << av[1] << std::endl;

	return 0;
}
