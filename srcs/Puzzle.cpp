/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Puzzle.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:35:56 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/08 22:09:44 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Puzzle.hpp"

using namespace	std;

static IHeuristic		*createManhattanHeuristic();

Puzzle::Puzzle():
	_heuristic(nullptr),
	_startNode(nullptr),
	_endNode(nullptr),
	_numberOfStates(0),
	_numberOfMoves(0),
	_solvabilityCheck(1),
	_mustBeSolvable(1)
{
}

Puzzle::~Puzzle()
{
	delete _heuristic;
	delete _startNode;
	delete _endNode;
}

IHeuristic const									*Puzzle::getHeuristic() const
{
	return _heuristic;
}

Node const											*Puzzle::getStartNode() const
{
	return _startNode;
}

Node const											*Puzzle::getEndNode() const
{
	return _endNode;
}

int													Puzzle::getMapSize() const
{
	return _mapSize;
}

int													Puzzle::getNumberOfStates() const
{
	return _numberOfStates;
}

int													Puzzle::getNumberOfMoves() const
{
	return _numberOfMoves;
}

std::string											Puzzle::getFilename() const
{
	return _filename;
}

bool												Puzzle::getSolvabilityCheck() const
{
	return _solvabilityCheck;
}

bool												Puzzle::getMustBeSolvable() const
{
	return _mustBeSolvable;
}






static IHeuristic									*createManhattanHeuristic()
{
	return (new Manhattan);
}

void												Puzzle::setHeuristic(std::string heuristic_name)
{
	typedef IHeuristic *(*func)();
	typedef struct {std::string name; func heuristic_func;} HeurCreateType;

	HeurCreateType			array[1] =
	{
		{"Manhattan", &createManhattanHeuristic}
	};

	for (auto &it: array)
	{
		if (!it.name.compare(heuristic_name))
			_heuristic = it.heuristic_func();
	}
}

void												Puzzle::setMapSize(int size)
{
	_mapSize = size;
}

void												Puzzle::setNumberOfStates(int nb)
{
	_numberOfStates = nb;
}

void												Puzzle::setNumberOfMoves(int nb)
{
	_numberOfMoves = nb;
}

void												Puzzle::setFilename(std::string filename)
{
	_filename = filename;
}

void												Puzzle::setSolvabilityCheck(bool state)
{
	_solvabilityCheck = state;
}

void												Puzzle::setMustBeSolvable(bool state)
{
	_mustBeSolvable = state;
}

/*
 * Check that input puzzle has no missing/duplicate numbers
 */
void												Puzzle::check_validity(std::vector<int> map, const int size)
{
	int			size_array = size * size;

	std::sort(map.begin(), map.end());

	if (map[0] != 0 || map[size_array - 1] != size_array - 1)
		throw ("invalid puzzle. Check for missing or duplicate numbers.");

	for (int i = 0; i < size_array - 1; i++)
	{
		if (map[i] != map[i + 1] - 1)
			throw ("invalid puzzle. Check for missing or duplicate numbers.");
	}
}

std::vector<int>									Puzzle::split_stoi(std::string line)
{
	std::stringstream			ss(line);
	std::vector<int>			splitted_str;
	std::string					tmp;
	std::string::size_type		sz;

	while (std::getline(ss, tmp, ' '))
	{
		if (!tmp.empty())
			splitted_str.push_back(std::stoi(tmp, &sz));
	}
	return (splitted_str);
}

std::vector<int>									Puzzle::parse_file(std::string const filename, unsigned long &size)
{
	std::ifstream				ifs(filename);
	std::string					str;
	std::string					line;
	std::size_t					hashtag_index;
	std::size_t					first_char_index;
	std::vector<int>			splitted_line;
	std::vector<int>			map;

	if (!ifs.is_open())
		throw ("failed to open file");

	while (std::getline(ifs, line))
	{
		if (line.empty())
			throw ("empty line found");
		
		if ((hashtag_index = line.find('#')) == std::string::npos)
			str = line;
		else if ((first_char_index = line.find_first_not_of(" ")) != hashtag_index)
			str = line.substr(first_char_index, hashtag_index);
		else
			continue ;

		if (str.find_first_not_of(" 0123456789") != std::string::npos)
			throw ("non-numeric character found (only exceptions are space ' ' and hashtag '#')");
		else if (str.find_first_of("0123456789") == std::string::npos)
			throw ("empty line found");

		splitted_line = split_stoi(str);

		if (!size)
		{
			if (splitted_line.size() > 1)
				throw ("wrong size definition");
			size = splitted_line[0];
			if (size < MAP_MIN_SIZE || size > MAP_MAX_SIZE)
				throw ("wrong size definition");
		}
		else
		{
			if (splitted_line.size() != size)
				throw ("wronged-sized line");
			map.insert(map.end(), splitted_line.begin(), splitted_line.end());
		}
	}

	if (map.empty())
		throw ("empty file");

	if (map.size() != size * size)
		throw ("wrong-sized map");

	return (map);
}

Node												*Puzzle::get_start_node_from_file(std::string filename)
{
	Node				*start_node;
	std::vector<int>	map;
	unsigned long 		size = 0;

	map = this->parse_file(filename, size);
	start_node = new Node(map, size);
	this->setMapSize(size);
	this->check_validity(map, size);

	return (start_node);
}

Node												*Puzzle::generate_random_start_node(Node *endNode, int must_be_solvable)
{
	Node	*node = new Node(*endNode);
	int		size = node->getMapSize();
	int		empty = node->getEmpty();
	int		rnd, x, y;

	srand(time(NULL));	// initialize random seed

	for (int steps = 0; steps < 1000; steps++)
	{
		y = empty / size;
		x = empty % size;
		rnd = rand() % 4 + 1;

		if (rnd == 1 && y > 0)	// move empty up
		{
			node->swap(empty, empty - size);
			empty -= size;
		}
		else if (rnd == 2 && y + 1 < size)	// move empty down
		{
			node->swap(empty, empty + size);
			empty += size;
		}
		else if (rnd == 3 && x > 0) // move empty left
		{
			node->swap(empty, empty - 1);
			empty -= 1;
		}
		else if (rnd == 4 && x + 1 < size) // move empty right
		{
			node->swap(empty, empty + 1);
			empty += 1;
		}
	}

	node->setEmpty(empty);

	if (!must_be_solvable)	// make unsolvable if option -u
	{
		if (node->getMap()[0] == 0 || node->getMap()[1] == 0)
			node->swap(size * size - 2, size * size - 1); // swap last 2 elems
		else
			node->swap(0, 1); // swap first 2 elems
	}

	return (node);
}


void												Puzzle::create_start_end_nodes()
{
	if (_filename.empty())
	{
		_endNode = this->create_end_node(_mapSize);
		_startNode = this->generate_random_start_node(_endNode, _mustBeSolvable);
	}
	else
	{
		try
		{
			_startNode = this->get_start_node_from_file(_filename); 
		}
		catch (const char *msg)
		{
			std::cerr << "Input file error: " << msg << std::endl;	
			return ;
		}
		_endNode = this->create_end_node(_mapSize);
	}
}

std::vector<int>									Puzzle::generate_resolved_array(int size)
{
	std::vector<std::vector<int>>		tmp(size, std::vector<int>(size));
	std::vector<int>					map;

	int minY = 0, minX = 0;
	int maxY = size, maxX = size;
	int	y, x;
	int i = 0;

	while (i < size * size)
	{
		y = minY;
		x = minX;

		while (x < maxX)
		{
			tmp[y][x] = i + 1;
			i++;
			x++;
		}
		minY++;

		x--;
		y++;
		while (y < maxY)
		{
			tmp[y][x] = i + 1;
			i++;
			y++;
		}
		maxX--;

		y--;
		x--;
		while (x >= minX)
		{
			tmp[y][x] = i + 1;
			i++;
			x--;
		}
		maxY--;

		x++;
		y--;
		while (y >= minY)
		{
			tmp[y][x] = i + 1;
			i++;
			y--;
		}
		minX++;
	}
	tmp[++y][x] = 0;

	for (auto &col: tmp)
	{
		for (auto &lin: col)
			map.push_back(lin);
	}
	return (map);
}

Node												*Puzzle::create_end_node(int size)
{
	std::vector<int>	resolved_map = this->generate_resolved_array(size);
	return(new Node (resolved_map, _mapSize));
}

int													Puzzle::count_inversions(std::vector<int> const &map, int size) const
{
	int		inversions = 0;

	for (int i = 0; i < (size * size - 1); i++)
	{
		for (int j = i + 1; j < (size * size); j++)
		{
			if (map[i] && map[j] && map[i] > map[j])
				inversions++;
		}
	}

	return (inversions);
}

bool												Puzzle::is_solvable(void) const
{
	int		start_inversions;
	int		end_inversions;

	if (!_startNode || !_endNode)
		return (0);

	start_inversions = this->count_inversions(_startNode->getMap(), _mapSize);
	end_inversions = this->count_inversions(_endNode->getMap(), _mapSize);

	if (this->_mapSize % 2 == 0)
	{
		start_inversions += (_startNode->getEmpty() / _mapSize);
		end_inversions += (_endNode->getEmpty() / _mapSize);
	}

	return (start_inversions % 2 == end_inversions % 2);
}
