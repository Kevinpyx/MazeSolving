/***********************************************************************
 * Homework: Maze Solving
 ***********************************************************************/

#include "queue.h"
#include "path.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void
queue_initialize (queue_t * queue) {
  queue->front = NULL;
  queue->rear = NULL;
}

bool
queue_empty (const queue_t * queue) {
  return (queue->front == NULL && queue->rear == NULL);
}

bool
enqueue (queue_t * queue, list_t* path) {
  node_t * newNode = malloc(sizeof(node_t));
  if (newNode == NULL)
    {printf ("could not allocate memory.\n");
      return false;}
  newNode->solution = path;
  newNode->next = NULL;

  if (queue_empty(queue)) {
    queue->rear = queue->front = newNode;
  }
  else {
  queue->rear->next = newNode;
  queue->rear = newNode;
  }
  return true;
}
/* returns whether item was successfully enqueued */

list_t *
dequeue (queue_t * queue) {
  assert (!queue_empty(queue));
  if (queue_empty (queue))
    {
    printf ("queue is empty\n");
    return NULL;
    }
  list_t * first = queue->front->solution;
  if (queue->front->next == NULL){
    free(queue->front);
    queue_initialize(queue);
    return first;
  }//if
  node_t * nextNode = queue->front->next;
  free(queue->front);
  queue->front = nextNode;
  return first;
}
/* returns string removed from queue */

list_t*
queue_front (const queue_t * queue) {
  assert (!queue_empty(queue));
  if (queue_empty (queue))
    {
    printf ("queue is empty\n");
    return NULL;
    }
  return queue->front->solution;
}

