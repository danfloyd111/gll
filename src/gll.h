#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* DATA STRUCTURES */

/* Element of the list */
typedef struct _node_t {
  void* data;
  int data_size; /* used only in get method */
  struct _node_t* prev;
  struct _node_t* next;
} node_t;

/* List structure */
typedef struct _list_t {
  node_t* head;
  node_t* tail;
  int length;
  int(*compare)(void*,void*); /*used to compare two data elements*/
  void(*mdealloc)(void*); /*used to free elements*/
} list_t;

/* FUNCTIONS */

/*
  DESCRIPTION: Creates a new empty list
  ARGUMENTS:
    comp - int function that takes two arguments
           used to compare two elements
    mdea - void function that takes one argument used to free
           the elements
  RETURNS the pointer to the newly created (empty) list
  ON ERROR: returns null and sets errno to ENOMEM if memory error
            occours / EINVAL if one of the arguments is null
*/
list_t* list (int(*comp)(void*,void*), void(*mdea)(void*));

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
    dsi - size of the element
  RETURNS 0 if the function terminates correctly
  ON ERROR: returns 1 and sets errno to ENOMEM if memory error
            occours / EINVAL if one of the arguments is null or
	    zero
*/
int push (list_t*, void*, int);

/*
  DESCRIPTION: Appends an element to the tail of the list passed
               as argument
  ARGUMENTS:
    dat - pointer to the element
    lis - ponter to the list
    dsi - size of the element
  RETURNS 0 if the function terminates correctly
  ON ERROR: returns 1 and sets errno to ENOMEM if memory error
            occours / EINVAL if one of the argument is null or
	    zero
*/
int append (list_t*, void*, int);

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
            arguments is null or ind < 0 or ind >= length(lis)
	    n.b. indexes start from 0 / ENODATA if the list
	    is empty
*/
int remove_element (list_t*, int);

/*
  DESCRIPTION: Returns a copy of the element at the index passed as
               argument if is contained in the list passed as argument
  ARGUMENTS:
    lis - pointer to the list
    ind - index of the element (count starts from 0)
  RETURNS the pointer to a copy of the element
  ON ERROR: returns NULL and sets errno to EINVAL if one of the arguments
            is null or ind < 0 or ind <= length(lis) / ENODATA if the list
	    is empty / ENOMEM if memory error occours
 */
void* get (list_t*, int);

/*
  DESCRIPTION: Sets the element at the index passed as argument with the
               data passed as argument
  ARGUMENTS:
    lis - pointer to the list
    dat - pointer to the new element
    ind - index of the element to set
  RETURNS 0 if the function ends correctly
  ON ERROR: returns 1 and sets errno to EINVAL if one of the arguments is
            null or ind < 0 or ind <= length(is) / ENODATA if the list is
            empty
*/
int set (list_t*, void*, int);

/*
  DESCRIPTION: Returns the index of the first occourence of the element
               passed as argument if is contained in the list passed as argument
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
  DESCRIPTION: Destroys the list and all its elements
  ARGUMENTS:
    lis - pointer to the list
  RETURNS void
  ON ERROR: -
  n.b. I decided to not check errors on free and do nothing if a null
       argument is passed to the function
*/
void destroy (list_t*);

/*
  DESCRIPTION: Returns a new list where all its elements are the result
               of the function passed as arguments applied to all the
               elements contained in the list passed as argument
  ARGUMENTS:
    lis - pointer to the list
    fun - pointer to the function
  RETURNS the pointer to the newly "mapped" list
  ON ERROR: returns null and sets errno to EINVAL if one of the arguments
            is null / ENODATA if the list passed as argument is empty
*/
list_t* map (list_t*, void*(*fun)(void*));

/*
  DESCRIPTION: Returns a new list where all its elements are the result
               of "filtering" the list passed as argument using the
               function passed as argument
  ARGUMENTS:
    lis - pointer to the list
    fun - pointer to the function
  RETURNS the pointer to the newly "filterd" list
  ON ERROR: returns null and sets errno to EINVAL if one of the arguments
            is null / ENODATA if the list passed as argument is empty
*/
list_t* filter (list_t*, int(*fun)(void*));
