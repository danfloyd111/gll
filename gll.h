#include <stdlib.h>
#include <string.h>

/* Element of the list */
typedef struct _node_t {
  void* data;
  _node* prev;
  _node* next;
} node_t;

/* List structure */
typedef struct _list_t {
  node* head;
  node* tail;

  int length;
  int nodeSize; /* this is not necessary - the size is fixed*/
} list_t;

/* FUNCTIONS */
