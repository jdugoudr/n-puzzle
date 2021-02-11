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
	std::ifstream				ifs(filename);
	std::string					str;
	std::string					line;
	std::size_t					found;
	std::vector<std::vector<int>>	split_vec;
	std::vector<int>			splitted;

	if (!ifs.is_open())
		throw ("Failed to open file");

	while (std::getline(ifs, line))
	{
		if (line.empty())
			throw ("Input file format error: empty line found");
		
		//std::cout << "line = " << line << std::endl;	

		found = line.find('#');
		str = (found == std::string::npos ? line : line.substr(0, found));

		if (!str.empty())
		{
			if (str.find_first_not_of(" 0123456789") != std::string::npos
			|| str.find_first_of("0123456789") == std::string::npos)
				throw ("Input file format error");

			//std::cout << " trimmed = " << str << std::endl;	

			splitted = split_stoi(str);
			/*std::cout << " splitted = |";	
			for (auto &it:splitted)
				std::cout << it << "|";	
			std::cout << std::endl;	*/

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

Node			*get_node_from_file(std::string filename)
{
	Node							*start_node = NULL;
	(void)start_node;
	std::vector<std::vector<int>>	splitted;
	unsigned long 					size = 0;

	try
	{
		splitted = parse_file(filename, size);
	}
	catch (const char *msg)
	{
		std::cerr << msg << std::endl;	
		return (NULL);
	}

	// check if valid
	// trier dans l'ordre croissant et checker si doublons/manquants
	// checker si le nb le + grand est bien (size * size - 1)

	// creer start_node

	start_node = create_start_node(splitted, size);

	/*for (auto & it:start_node->getMap())
	{
		for (auto & it2:it)
			std::cout << it2->getValue() << ", " << it2->getPosY() << ", " << it2->getPosX() << std::endl;		
	}

	std::cout << "EMPTY IS AT Y,X : " << start_node->getEmpty()->getPosY() << ", " << start_node->getEmpty()->getPosX() << std::endl;*/

	return (start_node);
}
