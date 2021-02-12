/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_start_end_nodes.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 22:43:16 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/12 23:10:10 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n-puzzle.hpp"

//Node			*create_start_node(std::vector<std::vector<int>> splitted, int size)
Node			*create_start_node(std::vector<int> splitted, int size)
{
	Node								*node;
//	Case								*new_case;
//	Case								*empty_case;
//	std::vector<std::vector<Case *>>	map;
//	std::vector<int>	map;

//	for (int y = 0; y < size; y++)
//	{
//		std::vector<Case *>	v1;
//		for (int x = 0; x < size; x++)
//		{
//			new_case = new Case(splitted[y][x], x, y);
//			v1.push_back(new_case);
//			if (new_case->getValue() == 0)
//				empty_case = new_case;
//		}
//		map.push_back(v1);
//	}

//	node = new Node(map, size);
	node = new Node(splitted, size);
//	node->setEmpty(empty_case);
	return (node);
}

//std::vector<std::vector<int>>				generate_resolved_array(int size)
std::vector<int>				generate_resolved_array(int size)
{
	std::vector<std::vector<int>>		resolved(size, std::vector<int>(size));
	std::vector<int>								result;

	int miny = 0, minx = 0;
	int maxy = size, maxx = size;
	int	y, x;
	int i = 0;

	while (i < size * size)
	{
		y = miny;
		x = minx;

		while (x < maxx)
		{
			resolved[y][x] = i + 1;
			i++;
			x++;
		}
		miny++;

		x--;
		y++;
		while (y < maxy)
		{
			resolved[y][x] = i + 1;
			i++;
			y++;
		}
		maxx--;

		y--;
		x--;
		while (x >= minx)
		{
			resolved[y][x] = i + 1;
			i++;
			x--;
		}
		maxy--;

		x++;
		y--;
		while (y >= miny)
		{
			resolved[y][x] = i + 1;
			i++;
			y--;
		}
		minx++;

		if (i == size * size)
			resolved[++y][x] = 0;
	}
	for (auto &col: resolved)
	{
		for (auto &lin: col)
			result.push_back(lin);
	}
	return (result);
//	return (resolved);
}

Node			*create_end_node(int size)
{
	Node								*node = NULL;
//	Case								*new_case;
//	Case								*empty_case;
//	std::vector<std::vector<Case *>>	map;

//	std::vector<std::vector<int>>		resolved = generate_resolved_array(size);
	std::vector<int>		resolved = generate_resolved_array(size);

//	for (int y = 0; y < size; y++)
//	{
//		std::vector<Case *>	v1;
//		for (int x = 0; x < size; x++)
//		{
//			new_case = new Case(resolved[y][x], x, y);
//			v1.push_back(new_case);
//			if (new_case->getValue() == 0)
//				empty_case = new_case;
//		}
//		map.push_back(v1);
//	}

	node = new Node(resolved, size);
//	node = new Node(map, size);
//	node->setEmpty(empty_case);

	return (node);
}
