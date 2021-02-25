/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n-puzzle.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 19:13:48 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/12 23:36:26 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLE_HPP
# define NPUZZLE_HPP

# include <iostream>
# include <string>
# include <array>
# include <unistd.h>

# include "Puzzle.hpp"

typedef struct	s_coord{
	int						col;
	int						lin;
}								t_coord;

int				usage(int ret, Puzzle *puzzle);
void			parse_arguments(int ac, char **av, Puzzle *puzzle);
std::string		choose_heuristic(void);

#endif
