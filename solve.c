/***********************************************************************
 * Homework: Maze Solving
 ***********************************************************************/

#include "queue.h"
#include "path.h"
#include "maze.h"
#include "position.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*
  function: path_start
  preconditions:
  maze points to a valid maze
  postconditions:
  the (position_t)start position of the maze is enqueued into (queue_t)paths as a list_t
  pointer to paths is returned
*/
queue_t*
path_start (maze_t * maze) {
  //make a queue for paths
  queue_t * paths = malloc(sizeof(queue_t));
  if (paths == NULL) {
    printf ("unable to allocate queue memory.\n");
    return NULL;
  }
  queue_initialize(paths);

  //make a list of positions that only contains the start position
  list_t * start_list = NULL;
    
  start_list = list_add(maze->start, start_list);
  
  //enqueue the start_list into path queue
  enqueue(paths, start_list);
    
  return paths;
}//path_start

/*
  function: end_reached
  preconditions:
  maze points to a valid maze
  paths points to a nopn-empty queue_t
  postconditions:
  return true if the end state of the front path is end of the maze
  return false otherwise
*/
bool
end_reached (maze_t * maze, queue_t * paths) {
  position_t current = paths->front->solution->position;
  return (maze->cells[offset(maze,current)] == END);
}//end_reached

/*
  function: pos_in_maze
  preconditions:
  maze points to a valid maze
  postconditions:
  return true if position if position is inside the maze
  return false otherwise
*/
bool
pos_in_maze (maze_t * maze, position_t pos) {
  return (pos.row >= 0 && pos.row < maze->height) && (pos.col >= 0 && pos.col < maze->width);
}//pos_in_maze

/*
  function: pos_reachable
  preconditions:
  maze points to a valid maze
  postconditions:
  return true if position is inside the maze and the cell at position is OPEN or END
  return false otherwise
*/
bool
pos_reachable (maze_t * maze, position_t pos) {
  if (pos_in_maze(maze, pos)) {
    cell_t cell_status = maze->cells[offset(maze,pos)];
    return (cell_status == OPEN || cell_status == END);
  }//
  return false;
}//pos_reachable
  
/*
  function: path_enqueue
  preconditions:
  paths points to a valid queue
  postconditions:
  add position to current path
  enqueue the augmented path to the queue
  return true if the new path is enqueued
  return false otherwise
*/
void
path_enqueue (queue_t * paths, list_t * cur_path, position_t position) {
  list_t * new_path = list_add(position, cur_path); //add position to path
  enqueue(paths, new_path); //enqueue path to paths and return
}//path_enqueue

/*
  function: traverse
  preconditions:
  maze points to a valid maze
  paths points to a valid queue_t structure
  postconditinos:
  return shortest path if end is reached
  if end is not reached
  mark current position as visited
  check the cell above, below, to the left of, and to the right of the current cell
  add reachable(OPEN, END) cell to the front path
  enqueue new front path into paths
  return NULL
*/
list_t*
traverse (maze_t* maze, queue_t* paths) {
  if (end_reached(maze, paths))
    return queue_front(paths);
  else {
    list_t * cur_path = dequeue(paths);
    position_t cur_pos = list_front(cur_path);
    maze->cells[offset(maze, cur_pos)] = VISITED;
        
    //enqueue the new path with end state above current position into paths
    position_t above = {cur_pos.row - 1, cur_pos.col};
    if (pos_reachable(maze, above))
      path_enqueue(paths, cur_path, above);
        
    //enqueue the new path with end state below current position into paths
    position_t below = {cur_pos.row + 1, cur_pos.col};
    if (pos_reachable(maze, below))
      path_enqueue(paths, cur_path, below);
        
    //enqueue the new path with end state left to current position into paths
    position_t left = {cur_pos.row , cur_pos.col - 1};
    if (pos_reachable(maze, left))
      path_enqueue(paths, cur_path, left);
        
    //enqueue the new path with end state right to current position into paths
    position_t right = {cur_pos.row, cur_pos.col + 1};
    if (pos_reachable(maze, right))
      path_enqueue(paths, cur_path, right);
        
    return NULL;
  }//if end is not reached
}//traverse

//main functino
int
main (void) {
  //read maze:
  maze_t * maze = readMaze(stdin);

  //return zero
  if (maze == NULL) {
    return 0;
  }
  
  //enqueue the paths with start position:
  queue_t * paths = path_start(maze);
  //now paths(queue) contains 1 path(list), the path contains the start position(position).
    
  list_t * solution;
  do {
    solution = traverse(maze, paths);

    //no more available path means END is unreachable
    if (queue_empty(paths)) {
      //no solution
      freeMaze(maze);
      return 0;
    }
  } while (solution == NULL);
  //keep traversing the maze until end is reached
    
  //printMaze(maze);
  list_print_reverse(solution);
  list_free (solution);
  freeMaze(maze);
    
  return 0;
}
