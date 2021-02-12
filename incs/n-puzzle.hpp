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

# define	MAP_MIN_SIZE		3
# define	MAP_MAX_SIZE		100

# include "Node.hpp"

# include <iostream>
# include <fstream>
# include <string>
# include <array>
# include <algorithm>

typedef struct	s_coord{
	int						col;
	int						lin;
}								t_coord;

Node			*get_node_from_file(std::string filename);
Node			*generate_start_node(void);
Node			*create_start_node(std::vector<int> splitted, int size);
Node			*create_end_node(int size);

#endif
