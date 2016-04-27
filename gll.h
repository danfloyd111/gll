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
  node* tail;
  int length;
  int(*compare)(void*,void*); /*used to compare two data elements*/
} list_t;

/* FUNCTIONS */

/*
  DESCRIPTION: Creates a new empty list
  ARGUMENTS:
    comp - int function that takes two arguments
           used to compare two elements
  RETURNS the pointer to the newly created (empty) list
  ON ERROR: returns null and sets errno to ENOMEM if memory error
            occours / EINVAL if one of the arguments is null
*/
list_t* list (int(*comp)(void*,void*));

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
               as argument
  ARGUMENTS:
    dat - pointer to the element
    lis - pointer to the list
  RETURNS 0 if the function terminates correctly
  ON ERROR: returns 1 and sets errno to ENOMEM if memory error
            occours / EINVAL if one of the arguments is null
*/
int push (void*, list_t*);

/*
  DESCRIPTION: Appends an element to the tail of the list passed
               as argument
  ARGUMENTS:
    dat - pointer to the element
    lis - ponter to the list
  RETURNS 0 if the function terminates correctly
  ON ERROR: returns 1 and sets errno to ENOMEM if memory error
            occours / EINVAL if one of the argument is null
*/
int append (void*, list_t*);

/*
  DESCRIPTION: Returns and remove the first element from the list
               passed as argument
  ARGUMENTS:
    lis - pointer to the list 
  RETURNS the first element of the list
  ON ERROR: returns NULL and sets errno to EINVAL if the argument
            is null / ENODATA if the list is empty
*/
void* pop (list_t*);

/*
  DESCRIPTION: Returns and remove the last element from the list
               passed as argument
  ARGUMENTS:
    lis - pointer to the list
  RETURNS the last element of the list
  ON ERROR: returns NULL and sets errno to EINVAL if the argument
            is null / ENODATA if the list is empty
*/
void* cut (list_t*);

/*
  DESCRIPTION: Removes the element at the position passed as
               argument from the list passed as argument
  ARGUMENTS:
    lis - pointer to the list
    ind - index of the element
  RETURNS 0 if the function ends correctly
  ON ERROR: returns 1 and sets errno to EINVAL if one of the
            arguments is null or -1 < ind < length(lis)
	    n.b. indexes start from 0 / ENODATA if the list
	    is empty
*/
int remove (list_t*, int);

/*
  DESCRIPTION: Returns the index of the element passed as argument
               if is contained in the list passed as argument
  ARGUMENTS:
    lis - pointer to the list
    dat - pointer to the element
  RETURNS the index of the element (count starts from 0)
  ON ERROR: returns -1 and sets errno to ENODATA if the element is 
            not contained in the list or if the list is empty /
            EINVAL if one of the arguments is null
	    n.b. this function perform a deep test, so it will compare
            the data itself, not the address
*/
int index_of (list_t*, void*);

/*
  DESCRIPTION: Returns the element at the index passed as argument
 */
void* get (list_t*, int);

/* NEED DOCS HERE */
int set (list_t*, int);
