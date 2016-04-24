#include "gll.h"

/* Please see gll.h for further informations */

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

/* Push new chunk of data in the head of the list */
int push (void* dat, list_t* lis) {
  if(dat == NULL || lis == NULL) {
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
  lis->head = this;
  lis->length ++;
  return 0;
}
