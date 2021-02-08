# N-Puzzle using A-star algorithm

This is a school project for testing A-Start algorithm in a N-Puzzle context.

## A-Star

This is a first-best-find algorithm usually use as pathfinding in video games.

It will find the shorest path between two point. Here we use it to find the way between two state. The state of the grid given as input at the begining of the program, and the goal state wich is the grid resolved.

It use Heurodistic functions wich will calculate a theoric cost to go from the actual state to the goal state.

## Heurodistic

In this project we implement :

### Manathan distance

This algorithm just do the addition of the move of all unwell placed value to their right place as if can move them straighly to their final position.

The given gird :
```
1 2 3
4 5  
6 7 8
```

Have a cost of 1 to reach the final state :
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

Have a cost of 4 to reach the final state :
```
1 2 3
4   5
6 7 8
```
(The number two have to do 2 moves, three and five, 1 move each).

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
