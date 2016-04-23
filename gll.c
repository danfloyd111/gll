#include "gll.h"

/* Please see gll.h for further informations */

/* Create new list */
list_t* list() {
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
