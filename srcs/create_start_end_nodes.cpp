#include "n-puzzle.hpp"

Node			*create_start_node(std::vector<std::vector<int>> splitted, int size)
{
	Node								*node;
	Case								*new_case;
	Case								*empty_case;
	std::vector<std::vector<Case *>>	map;

	for (int y = 0; y < size; y++)
	{
		std::vector<Case *>	v1;
		for (int x = 0; x < size; x++)
		{
			new_case = new Case(splitted[y][x], x, y);
			v1.push_back(new_case);
			if (new_case->getValue() == 0)
				empty_case = new_case;
		}
		map.push_back(v1);
	}

	node = new Node(map, size);
	node->setEmpty(empty_case);
	return (node);
}

Node			*create_end_node(int size)
{
	(void)size;
	/*Node								*node;
	Case								*new_case;
	std::vector<std::vector<Case *>>	map(size);

	int y = 0;
	int x = 0;

	while (y < size)
	{
		std::vector<Case *> v1(size);

		// seouifhsieurghospeirghjoisejgoij
	
		y++;
	}

	node = new Node(map, size);

	// last case = empty case
	return (node);*/
	return (NULL);
}

