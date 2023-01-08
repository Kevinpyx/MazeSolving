# MazeSolving
Using BFS to find the shortest path in a maze from Start to End if there exists one


## To use the program
Make the file with the Makefile provided. To run it in the terminal window: type ./solve < maze.txt where maze.txt is a maze file (Maze files can be generated using the amaze.c file provided).


## Maze file format
The first line of a maze file should be the dimensions of the grid—two positive integers, representing the height and width, respectively.

The maze grid is given next. It will consist of an H×W matrix of characters, where
- a space represents an open cell,
- S represents the start cell,
- E represents the end cell, and
- any other character represents a blocked cell.
