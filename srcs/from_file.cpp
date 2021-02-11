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

std::vector<std::vector<int>>		parse_file(std::string filename, unsigned long &size)
{
	std::ifstream					ifs(filename);
	std::string						str;
	std::string						line;
	std::size_t						found;
	std::vector<std::vector<int>>	split_vec;
	std::vector<int>				splitted;

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
				split_vec.push_back(splitted);
			}
		}
	}

	if (split_vec.size() > size)
		throw ("Input file format error: wrong-sized map");

	return (split_vec);
}

int				check_if_valid(std::vector<std::vector<int>> puzzle_vec, const int size)
{
	int			i = 0;
	int			size_array = size * size;
	int			array[size_array];

	for (auto &it: puzzle_vec)
	{
		for (auto &it2: it)
			array[i++] = it2;
	}
	std::sort(array, array + size_array);

	if (array[0] != 0 || array[size_array - 1] != size_array - 1)
		throw ("Invalid puzzle. Check for missing or duplicate numbers.");

	for (int i = 0; i < size_array - 1; i++)
	{
		if (array[i] != array[i + 1] - 1)
			throw ("Invalid puzzle. Check for missing or duplicate numbers.");
	}

	return (0);
}

Node			*get_node_from_file(std::string filename)
{
	Node							*start_node = NULL;
	std::vector<std::vector<int>>	puzzle_vec;
	unsigned long 					size = 0;

	try
	{
		puzzle_vec = parse_file(filename, size);
		check_if_valid(puzzle_vec, size);
	}
	catch (const char *msg)
	{
		std::cerr << msg << std::endl;	
		return (NULL);
	}

	start_node = create_start_node(puzzle_vec, size);

	return (start_node);
}
