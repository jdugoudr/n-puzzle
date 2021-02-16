/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_file.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 22:45:40 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/12 23:32:53 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n-puzzle.hpp"
#include <sstream>
#include <vector>

std::vector<int>					split_stoi(std::string line)
{
	std::vector<int>			vec;
	std::stringstream			ss(line);
	std::string					token;
	std::string::size_type		sz;

	while (std::getline(ss, token, ' '))
	{
		if (!token.empty())
			vec.push_back(std::stoi(token, &sz));
	}
	return (vec);
}

std::vector<int>		parse_file(std::string filename, unsigned long &size)
{
	std::ifstream				ifs(filename);
	std::string					str;
	std::string					line;
	std::size_t					found;
	std::vector<int>			split_vec;
	std::vector<int>			splitted;

	if (!ifs.is_open())
		throw ("Failed to open file");

	while (std::getline(ifs, line))
	{
		if (line.empty())
			throw ("Input file format error: empty line found");
		
		found = line.find('#');
		str = (found == std::string::npos ? line : line.substr(0, found));

		if (!str.empty())
		{
			if (str.find_first_not_of(" 0123456789") != std::string::npos
			|| str.find_first_of("0123456789") == std::string::npos)
				throw ("Input file format error");

			splitted = split_stoi(str);

			if (!size)
			{
				if (splitted.size() > 1)
					throw ("Input file format error: wrong size definition");
				size = splitted[0];
				if (size < MAP_MIN_SIZE || size > MAP_MAX_SIZE)
					throw ("Input file format error: wrong size definition");
			}
			else
			{
				if (splitted.size() != size)
					throw ("Input file format error: wronged-sized line");
				split_vec.insert(split_vec.end(), splitted.begin(), splitted.end());
			}
		}
	}

	if (split_vec.empty())
		throw ("Empty file");

	if (split_vec.size() != size * size)
		throw ("Input file format error: wrong-sized map");

	return (split_vec);
}

int				check_if_valid(std::vector<int> puzzle_vec, const int size)
{
	int			size_array = size * size;

	std::sort(puzzle_vec.begin(), puzzle_vec.end());

	if (puzzle_vec[0] != 0 || puzzle_vec[size_array - 1] != size_array - 1)
		throw ("Invalid puzzle. Check for missing or duplicate numbers.");

	for (int i = 0; i < size_array - 1; i++)
	{
		if (puzzle_vec[i] != puzzle_vec[i + 1] - 1)
			throw ("Invalid puzzle. Check for missing or duplicate numbers.");
	}

	return (0);
}

/*Node			*get_node_from_file(std::string filename)
{
	Node							*start_node = NULL;
	std::vector<int>	puzzle_vec;
	unsigned long 		size = 0;

	try
	{
		puzzle_vec = parse_file(filename, size);
		check_if_valid(puzzle_vec, size);
	}
	catch (const char *msg)
	{
		std::cerr << "Error: " << msg << std::endl;	
		return (NULL);
	}

	start_node = create_start_node(puzzle_vec, size);

	return (start_node);
}*/
