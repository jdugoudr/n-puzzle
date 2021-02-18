/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:18:18 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/18 17:23:32 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	NODE_HPP
# define NODE_HPP

//# include "Case.hpp"
# include <iomanip>
# include <iostream>
# include <vector>

struct								Node{
	std::vector<int>					_map;
	int									_fscore;
	Node								*_parent;
	int									_gscore;
	int									_empty;
	bool								_isOpen;
	int									_mapSize;

	Node();
	Node(std::vector<int> m, int s);
	Node(Node const &o, Node *p);
	Node(std::vector<int> m, Node *p, int g, int f, int e, int s);

	bool	operator>(const Node &p) const;
	bool	operator==(const Node &p) const;
	static bool	comp(Node *a, Node *b);
};

std::ostream	&operator<<(std::ostream &o, Node const &c);

#endif

