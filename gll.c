#include "gll.h"
/* Please see gll.h for further informations */

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

/* Return and remove the first element from the list */
void* pop (list_t* lis) {
  node_t* f = NULL;
  void* e = NULL;
  if(lis) {
    if(!length(lis))
      errno = ENODATA;
    else {
      f = lis->head;
      e = f->data;
      if(length(lis)==1)
	tail = NULL;
      else
	f->next->prev = NULL;
      lis->head = f->next;
      free(f);
    }
  } else {
    errno = EINVAL;
  }
  return e;
}
