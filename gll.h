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
  DESCRIPTION: Returns the length of the list passed as argument
  ARGUMENTS:
    lis - pointer to the list
  RETURNS the length of the list
  ON ERROR: returns -1 and sets errno to EINVAL if the argument
            is null
*/
int length (list_t*);

/*
  DESCRIPTION: Inserts an element in the head of the list passed
               as arguments
  ARGUMENTS:
    dat - pointer to the element
    lis - pointer to the list
  RETURNS 0 if the function terminates correctly
  ON ERROR: returns 1 and sets errno to ENOMEM if memory error
            occours / EINVAL if one of the arguments is null
*/
int push (void*, list_t*);

/*
  DESCRIPTION: Returns and remove the first element from the list
  ARGUMENTS:
    lis - pointer to the list 
  RETURNS the first element of the list
  ON ERROR: returns NULL and sets errno to EINVAL if the argument
            is null / ENODATA if the list is empty
*/
void* pop (list_t*);
