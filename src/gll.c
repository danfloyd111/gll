#include "gll.h"
/* Please see gll.h for further informations */

/* IMPLEMENTATION */

/* Create new list */
list_t* list (int(*comp)(void*,void*), void(*mdea)(void*)) {
  list_t* this;
  if(comp == NULL) {
    errno = EINVAL;
    return NULL;
  }
  if(!(this = (list_t*) malloc(sizeof(list_t)))) {
    errno = ENOMEM;
    return NULL;
  }
  this->head = NULL;
  this->tail = NULL;
  this->length = 0;
  this->compare = comp;
  this->mdealloc = mdea;
  return this;
}

/* Return the length of the list */
int length (list_t* lis) {
  if(!lis) {
    errno = EINVAL;
    return -1;
  } else return lis->length;
}

/* Insert an element in the head of the list */
int push (list_t* lis, void* dat) {
  if(!dat || !lis) {
    errno = EINVAL;
    return 1;
  }
  node_t* this;
  if(!(this = (node_t*) malloc(sizeof(node_t)))) {
    errno = ENOMEM;
    return 1;
  }
  this->data = dat;
  this->prev = NULL;
  this->next = lis->head;
  if(!length(lis))
    lis->tail = this;
  else
    this->next->prev = this;
  lis->head = this;
  lis->length ++;
  return 0;
}

/* Append an element to the tail of the list */
int append (list_t* lis, void* dat) {
  if (!dat || !lis) {
    errno = EINVAL;
    return 1;
  }
  node_t* this;
  if(!(this = (node_t*) malloc(sizeof(node_t)))) {
    errno = ENOMEM;
    return 1;
  }
  this->data = dat;
  this->next = NULL;
  this->prev = lis->tail;
  if(!length(lis))
    lis->head = this;
  else
    this->prev->next = this;
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
int remove_element (list_t* lis, int ind) {
  if(!length(lis)) {
    errno = ENODATA;
    return 1;
  }
  if(ind < 0 || ind >= length(lis)) {
    errno = EINVAL;
    return 1;
  }
  node_t* it = lis->head;
  int old_ind = ind;
  while (ind) {
    it = it->next;
    ind--;
  }
  lis->mdealloc(it->data);
  /* list merging */
  if(it->prev != NULL)
    it->prev->next = it->next;
  if(it->next != NULL)
    it->next->prev = it->prev;
  /* head or tail removal */
  if(old_ind == 0)
    lis->head = it->next;
  if(old_ind == (length(lis)-1))
    lis->tail = it->prev;
  lis->length --;
  free(it);
  return 0;
}

/* Return the element at specified index*/
void* get (list_t* lis, int ind) {
  if(lis == NULL || ind < 0 || ind > length(lis)-1) {
    errno = EINVAL;
    return NULL;
  }
  if(length(lis) == 0) {
    errno = ENODATA;
    return NULL;
  }
  node_t* it = lis->head;
  while(ind) {
    it = it->next;
    ind --;
  }
  return it->data;
}

/* Set the element at specified index with the element
   passed as argument */
int set (list_t* lis, void* dat, int ind) {
  if(lis == NULL || ind < 0 || ind > length(lis)-1) {
    errno = EINVAL;
    return 1;
  }
  if(length(lis) == 0) {
    errno = ENODATA;
    return 1;
  }
  node_t* it = lis->head;
  while(ind) {
    it = it->next;
    ind --;
  }
  lis->mdealloc(it->data);
  it->data = dat;
  return 0;
}

/* Return the index of the element */
int index_of (list_t* lis, void* dat) {
  int ind = -1;
  if(!lis || !dat) {
    errno = EINVAL;
    return ind;
  }
  int len = length(lis);
  if(len) {
    int flag = 1;
    ind++;
    while(ind < len && flag){
      if(lis->compare(get(lis,ind),dat) == 0)
	flag = 0;
      ind++;
    }
    if(!flag) {
      ind--;
      return ind;
    }
  }
  errno = ENODATA;
  return -1;
}

/* Destroy the list and all of its elements */
void destroy (list_t* lis) {
  if(lis) {
    node_t* it = lis->head;
    if(it) {
      node_t* el;
      while(it) {
	el = it;
	it = it->next;
	lis->mdealloc(el);
      }
    }
    free(lis);
  }
}

/* Return a new list mapped with the function passed
   as argument */
list_t* map (list_t* lis, void*(*fun)(void*)) {
  if(!lis || !fun) {
    errno = EINVAL;
    return NULL;
  }
  if(!length(lis)) {
    errno = ENODATA;
    return NULL;
  }
  list_t* nl = list(lis->compare, lis->mdealloc);
  node_t* it = lis->head;
  while(it) {
    append(nl, fun(it->data));
    it = it->next;
  }
  return nl;
}

/* Return a new list filtered with the function passed
   as argument */
list_t* filter (list_t* lis, int(*fun)(void*)) {
  if(!lis || !fun) {
    errno = EINVAL;
    return NULL;
  }
  if(!length(lis)) {
    errno = ENODATA;
    return NULL;
  }
  list_t* nl = list(lis->compare, lis->mdealloc);
  node_t* it = lis->head;
  while(it) {
    if(fun(it->data))
      append(nl,it->data);
    it = it->next;
  }
  return nl;
}
