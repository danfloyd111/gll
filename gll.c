#include "gll.h"
/* Please see gll.h for further informations */

/* IMPLEMENTATION */

/* Create new list */
list_t* list (int(*comp)(void*,void*)) {
  list_t* this;
  if(comp == NULL) {
    errno = EINVAL;
    return NULL;
  }
  if(!(this = malloc(sizeof(list_t)))) {
    errno = ENOMEM;
    return NULL;
  }
  this->head = NULL;
  this->tail = NULL;
  this->length = 0;
  this->compare = comp;
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
      /* data cannot be null -> see gll.h */
      e = f->data; 
      if(length(lis)==1)
	lis->tail = NULL;
      else
	f->next->prev = NULL;
      lis->head = f->next;
      /* I decided to not check memory errors on free */
      free(f); 
      lis->length --;
    }
  } else {
    errno = EINVAL;
  }
  return e;
}

/* Return and remove the last element from the list */
void* cut (list_t* lis) {
  node_t* l = NULL;
  void* e = NULL;
  if(lis) {
    if(!length(lis))
      errno = ENODATA;
    else {
      l = lis->tail;
      /* data cannot be null -> see gll.h */
      e = l->data;
      if(length(lis)==1)
	lis->head = NULL;
      else
	l->prev->next = NULL;
      lis->tail = l->prev;
      /* I decided to not check memory errors on free  */
      free(l);
      lis->length --;
    }
  } else {
    errno = EINVAL;
  }
  return e;
}

/* Remove an element from the list */
int remove (list_t* lis, int ind) {
  if(!length(lis)) {
    errno = ENODATA;
    return 1;
  }
  if(ind < 0 || ind >= length(lis)) {
    errno = EINVAL;
    return 1;
  }
  node_t* it = lis->head;
  while (ind) {
    it = it->next;
    ind--;
  }
  free(it->data);
  /* list merging */
  if(it->prev)
    it->prev->next = it->next;
  if(it->next)
    it->next->prev = it->prev;
  /* head or tail removal */
  if(ind == 0)
    lis->head = it->next;
  if(ind == (length(lis)-1))
    lis->tail = it->prev;
  list->length --;
  free(it);
  return 0;
}

/* Returns the index of the element */
int index_of (list_t* lis, void* dat) {
  int ind = -1;
  if(!lis || !dat) {
    errno = EINVAL;
    return ind;
  }
  int len = length(lis);
  if(len) {
    node_t* it = lis->head;
    for(int j=0; j<len; j++) {
      /* NEED GET & SET FUNCTIONS HERE */
    }
  }
}
