#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* DATA STRUCTURES */
 
/* Element of the list */
typedef struct _node_t {
  void* data;
  _node* prev;
  _node* next;
} node_t;

/* List structure */
typedef struct _list_t {
  node* head;
  node* tail; /* maybe is not necessary */

  int length;
} list_t;

/* FUNCTIONS */

/*
  DESCRIPTION: Creates a new empty list
  ARGUMENTS: none
  RETURNS the pointer to the newly created (empty) list
  ON ERROR: returns null and sets errno to ENOMEM
*/
list_t* list();
