#include "gll.h"

/* Please see gll.h for further informations */

/* HELPERS */

/* Remove an element and its content */
void h_remove (node_t* this) {
  if(this) {
    node_t p = this->prev, n = this->next;
    if (p)
      p->next = n;
    if (n)
      n->prev = p;
    if (this->data)
      free(data);
    free(this);
  }
}

/* IMPLEMENTATION */

/* Create new list */
list_t* list () {
  list_t* this;
  if(!(this = malloc(sizeof(list_t)))) {
    errno = ENOMEM;
    return NULL;
  }
  this->head = NULL;
  this->tail = NULL;
  this->length = 0;
  return this;
}

/* Return the length of the list */
int length (list_t lis) {
  if(!lis) {
    errno = EINVAL;
    return -1;
  } else return lis->length;
}

/* Insert an element in the head of the list */
int push (void* dat, list_t* lis) {
  if(!dat || !lis) {
    errno = EINVAL;
    return 1;
  }
  node_t* this;
  if(!(this = malloc(sizeof(node_t)))) {
    errno = ENOMEM;
    return 1;
  }
  this->data = dat;
  this->prev = NULL;
  this->next = lis->head;
  if(!length(lis))
    lis->tail = this;
  lis->head = this;
  lis->length ++;
  return 0;
}

/* Append an element to the tail of the list */
int append (void* dat, list_t* lis) {
  if (!dat || !lis) {
    errno = EINVAL;
    return 1;
  }
  node_t* this;
  if(!(this = malloc(sizeof(node_t)))) {
    errno = ENOMEM;
    return 1;
  }
  this->data = dat;
  this->next = NULL;
  this->prev = lis->tail;
  if(!length(lis))
    lis->head = this;
  lis->tail = this;
  lis->length ++;
  return 0;
}
