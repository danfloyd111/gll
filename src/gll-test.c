#include <stdio.h>
#include <string.h>

#include "gll.h"

#define NO_ERROR 0
#define NUM_ELEMENTS 100

/* element used for test */
typedef struct _item {
  char* name;
  int cost;
  int weight;
  int quantity;
} item;

int cmp (void* d1, void* d2) {
  item* i1 = (item*) d1;
  item* i2 = (item*) d2;
  return strcmp((char*) i1->name, (char*) i2->name);
}

void mde (void* itm) {
  item* i = (item*) itm;
  /* in this case the next line is useless and dangerous
     because i decided to allocate names of the items
     on the stack, not on the heap !!! If you want to 
     allocate them on the heap uncomment the next line
     in order to not waste memory.
  */
  /*free(i->name);*/
  free(i);
}

/* element used for the second part of test */
typedef struct _int_item {
  int val;
} int_item;

int cmp_int (void* d1, void* d2) {
  int_item* i1 = (int_item*) d1;
  int_item* i2 = (int_item*) d2;
  if(i1->val > i2->val)
    return 1;
  if(i1->val < i2->val)
    return -1;
  return 0;
}

void mde_int (void* itm) {
  int_item* i = (int_item*) itm;
  free(i);
}

/* *** */

void my_assert (int condition, int error) {
  if(!condition && error == errno) {
    printf("Error detected\t\t-> TEST PASSED\n");
  } else if(condition && error == NO_ERROR) {
    printf("Correct behaviour\t-> TEST PASSED\n");
  } else {
    printf("Error detected\t-> TEST NOT PASSED\n");
    printf("Possible causes:\n");
    printf("+ wrong error detection\n");
    printf("+ the operation performed is bugged\n");
    printf("+ error not fired\n");
    exit(1);
  }
}

/* *** */

int main () {
 
  printf("List allocation...\t");
  list_t* l = NULL;
  my_assert(((l = list(cmp,mde)) != NULL), NO_ERROR);
  printf("List einval...    \t");
  list_t* l1 = NULL;
  my_assert(((l1 = list(NULL,NULL)) != NULL), EINVAL);

  printf("Zero length...    \t");
  my_assert(((length(l)) == 0), NO_ERROR);

  printf("Pop enodata...    \t");
  my_assert((pop(l) != NULL), ENODATA);

  printf("Cut enodata...    \t");
  my_assert((cut(l) != NULL), ENODATA);

  printf("Remove enodata... \t");
  my_assert((remove_element(l,0) == 0), ENODATA);
  
  printf("Push einval...    \t");
  my_assert(((push(NULL,NULL,0)) == 0), EINVAL);

  printf("Zero length again...\t");
  my_assert(((length(l)) == 0), NO_ERROR);

  printf("Push element...     \t");
  item* el = (item*) malloc(sizeof(item));
  char* n = "banana";
  el->name = (char*) malloc(sizeof(char)*(strlen(n)+1));
  el->cost = 2;
  el->weight = 1;
  el->quantity = 100;
  my_assert(((push(l, (void*)el, sizeof(item))) == 0), NO_ERROR);

  printf("Length after push...\t");
  my_assert(((length(l)) == 1), NO_ERROR);

  printf("Append einval...    \t");
  my_assert(((append(NULL, NULL, 0)) == 0), EINVAL);

  printf("Length again...     \t");
  my_assert(((length(l)) == 1), NO_ERROR);
  
  printf("Append element...   \t");
  item* el1 = (item*) malloc(sizeof(item));
  char* n1 = "apple";
  el1->name = n1;
  el1->cost = 1;
  el1->weight = 2;
  el1->quantity = 150;
  my_assert(((append(l, (void*) el1, sizeof(item))) == 0), NO_ERROR);

  printf("Length after append...\t");
  my_assert(((length(l)) == 2), NO_ERROR);

  printf("Push another element...\t");
  item* el2 = (item*) malloc(sizeof(item));
  char* n2 = "strawberry";
  el2->name = n2;
  el2->cost = 4;
  el2->weight = 1;
  el2->quantity = 30;
  my_assert(((push(l, (void*) el2, sizeof(item))) == 0), NO_ERROR);

  printf("append again...    \t");
  item* el3 = (item*) malloc(sizeof(item));
  char* n3 = "pear";
  el3->name = n3;
  el3->cost = 2;
  el3->weight = 2;
  el3->quantity = 50;
  my_assert(((append(l, (void*) el3, sizeof(item))) == 0), NO_ERROR);

  printf("Length again...    \t");
  my_assert(((length(l)) == 4), NO_ERROR);

  printf("Pop einval...      \t");
  my_assert((pop(NULL)!=NULL), EINVAL);

  printf("Length again...    \t");
  my_assert(((length(l)) == 4), NO_ERROR);

  printf("Pop...             \t");
  item* t = NULL;
  my_assert((((t = (item*) pop(l)) != NULL)&&
	     (strcmp(t->name,"strawberry") == 0)), NO_ERROR);
  mde(t);

  printf("Length after pop  \t");
  my_assert(((length(l)) == 3), NO_ERROR);

  printf("Cut einval...     \t");
  my_assert((cut(NULL)!= NULL), EINVAL);

  printf("Length again...    \t");
  my_assert(((length(l)) == 3), NO_ERROR);

  printf("Cut...             \t");
  item* t1 = NULL;
  my_assert((((t = (item*) cut(l)) != NULL)&&
	     (strcmp(t->name,"pear") == 0)), NO_ERROR);
  mde(t1);

  printf("Length after cut...\t");
  my_assert(((length(l)) == 2), NO_ERROR);
  
  printf("Remove einval...    \t");
  my_assert((remove_element(NULL, 42) == 0), EINVAL);

  printf("Length again...     \t");
  my_assert(((length(l)) == 2), NO_ERROR);

  printf("Remove...           \t");
  my_assert((remove_element(l, 1) == 0), NO_ERROR);

  printf("Length after remove...\t");
  my_assert(((length(l)) == 1), NO_ERROR);

  printf("Remove again...       \t");
  my_assert((remove_element(l, 0) == 0), NO_ERROR);

  printf("Length after remove...\t");
  my_assert(((length(l)) == 0), NO_ERROR);
  
  printf("List destruction...\tCorrect behaviour\t-> TEST PASSED\n");
  destroy(l);

  printf("End of first test battery...\n");
  
  printf("Setting up a new environment...\n");

  printf("List allocation...\t");
  list_t* int_list = NULL;
  my_assert(((int_list = list(cmp_int,mde_int)) != NULL), NO_ERROR);
  
  /* Creating some new elements */

  int_item* ptr = NULL;
  for(int i=0; i<NUM_ELEMENTS; i++) {
    ptr = (int_item*) malloc(sizeof(int_item));
    if(ptr == NULL){
      fprintf(stderr, "Memory allocation failed\n");
      return 1;
    }
    ptr->val = i;
    append(int_list, (void*) ptr, sizeof(int_item));
  }

  printf("Checking length...\t");
  my_assert(((length(int_list)) == NUM_ELEMENTS), NO_ERROR);

  printf("List destruction...\tCorrect behaviour\t-> TEST PASSED\n");
  destroy(int_list);

  printf("End of second test battery...\n");

  return 0;
}
