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
    perror("Error detected\t\t-> TEST PASSED\n");
  } else if(condition && error == NO_ERROR) {
    printf("Correct behaviour\t\t-> TEST PASSED\n");
  } else {
    printf("Error detected\t\t-> TEST NOT PASSED\n");
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
  printf("List destruction...\tUnchecked behaviour, see gll.h\t-> TEST PASSED\n");
  destroy(l);
  return 0;
}
