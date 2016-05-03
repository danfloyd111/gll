#include <stdio.h>
#include <string.h>

#include "gll.h"

#define NO_ERROR 0

/* element used for test */
typedef struct _item {
  char* name;
  int cost;
  int weight;
  int quantity;
} item;

int cmp (void* s1, void* s2) {
  return strcmp((char*) s1, (char*) s2);
}

void mde (void* itm) {
  item* i = (item*) itm;
  free(i->name);
  free(i);
}

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

int main () {
 
  printf("List allocation...\t");
  list_t* l = NULL;
  my_assert(((l = list(cmp,mde)) != NULL), NO_ERROR);
 
  printf("List einval...    \t");
  list_t* l1 = NULL;
  my_assert(((l1 = list(NULL,NULL)) != NULL), EINVAL);

  printf("Zero length...    \t");
  my_assert(((length(l)) == 0), NO_ERROR);

  printf("Push einval...    \t");
  my_assert(((push(NULL,NULL)) == 0), EINVAL);

  printf("Zero length again...\t");
  my_assert(((length(l)) == 0), NO_ERROR);

  printf("Push element...     \t");
  item* el = (item*) malloc(sizeof(item));
  char* n = "banana";
  el->name = (char*) malloc(sizeof(char)*(strlen(n)+1));
  el->cost = 2;
  el->weight = 1;
  el->quantity = 100;
  my_assert(((push((void*)el, l)) == 0), NO_ERROR);

  printf("Length after push...\t");
  my_assert(((length(l)) == 1), NO_ERROR);

  printf("List destruction...\tCorrect behaviour\t-> TEST PASSED\n");
  destroy(l);

  return 0;
}
