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
  ON ERROR: returns null and sets errno to ENOMEM if memory error
            occours
*/
list_t* list ();

/*
  DESCRIPTION: Inserts the chunk of data in the head of the list
  ARGUMENTS:
    dat - pointer to the chunk of data to insert
    lis - pointer to the list
  RETURNS 0 if the function terminates correctly
  ON ERROR: returns 1 and sets errno to ENOMEM if memory error
            occours / EINVAL if one of the arguments is null
*/
int push (void*, list_t*);
