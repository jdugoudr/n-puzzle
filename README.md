# N-Puzzle using A-star algorithm

This is a school project for testing A-Star algorithm in a N-Puzzle context.

## A-Star

This is a first-best-find algorithm usually use as pathfinding in video games.

It will find the shorest path between two point. Here we use it to find the way between two state. The state of the grid given as input at the begining of the program, and the goal state wich is the grid resolved.

It use Heurodistic functions wich will calculate a theoric cost to go from the actual state to the goal state.

## Heuristics

All heuristics used in this project are admissible, i.e. they never overestimate the cost of reaching the goal.
In this project we implement the following heuristic functions:

### Hamming

This heuristic counts all the misplaced tiles on a state, compared to the goal state.

The given gird:
```
1 2 3
8 4  
5 6 7
```
has a cost of 3 to reach the final state:
```
1 2 3
8   4
7 6 5
```
(tiles 4, 5, 7 are misplaced)


### Manathan distance

This algorithm does the addition of the moves from all misplaced tiles to their goal place, without taking into account the tiles on their way.

The given gird :
```
1 2 3
4 5  
6 7 8
```

Has a cost of 1 to reach the final state :
```
1 2 3
4   5
6 7 8
```

This one  :
```
1 3  
4 5 2 
6 7 8
```

Has a cost of 4 to reach the final state :
```
1 2 3
4   5
6 7 8
```
(tile 2 has to do two moves, tiles 3 and 5 have to do one move each)


### Linear Conflicts

This algorithm calculates the Manhattan Distance of each tile (the number of moves in the path from a tile to its goal), and adds the number of conflicts that may appear on that path.

Two tiles A and B are in linear conflict if :
 - they are on the same line
 - their goal positions also are on this line
 - A is to the right of B, and the goal position of A is to the left of the goal position of B.

For each line and column of the goal map, we look for tiles in conflict, and add a cost of 2 for each conflicting pair.

When 3 or more tiles are in linear conflict, we pick the tile involved in the most conflicts to move first. This way we can minimize the number of additional moves, and the heuristic stays admissible.

The given grid:
```
3 1 2
8   4
7 6 5
```
has a cost of 6 to reach the final state:
```
1 2 3
8   4
7 6 5
```
Manhattan distance = 4 (tile 3 moves two times, tile 1 moves one time, tile 2 moves one time)
	+
Conflicts = 2 (tile 3 conflicts with tiles 1 and 2. So we move 3 first in order to avoid extra moves. So 1 conflict * 2)
	= 6



# Developement information

Their are a test directory wich provide some cpp files.

This files are used as unary test to test classes we will developt.

For instance the file test/case.cpp is simple main function to test or Case class.

To compile and run the test :
```
make case
./test/case
```

To clean the test/case binary :
```
make fclean
```
