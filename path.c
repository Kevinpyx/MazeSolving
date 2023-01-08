/***********************************************************************
 * Homework: Maze Solving
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "path.h"
#include "position.h"
#include <assert.h>

list_t *
list_add ( position_t position, list_t* current) {
  list_t * added = malloc (sizeof(list_t));
  if (added == NULL) {
    printf ("Unable to allocate memory.\n");
    return NULL;
  }//check for NULL
    
  added->position = position;
  added->next = current;
  return added;
}//list_add


position_t
list_front (list_t* current) {
  assert (current != NULL);
  return current->position;
}//list_front


void
list_print_reverse ( list_t* list) {
  if (list != NULL) {
    list_print_reverse(list->next);
    position_t pos = list_front(list);
    printf ("%d,%d\n", pos.row, pos.col);
  }
  else return;
}//list_print_reverse


void
list_free (list_t* list) {
  list_t * cur = list, * nextPos = list->next;
  for (;cur->next != NULL;
       cur = nextPos, nextPos = nextPos->next) {
    free(cur);
  }//loop
  free (cur);
}//list_free
