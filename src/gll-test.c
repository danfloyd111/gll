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

void* double_val (void* itm) {
  /*
    n.b. in order to preserve the original elements, it's
    recommended to make a new element instead of use the
    same provided as argument
  */
  int_item* v = (int_item*) itm;
  int_item* ni = (int_item*) malloc(sizeof(int_item));
  if(!ni){
    fprintf(stderr,"Memory allocation failed\n");
    exit(1);
  }
  ni->val = v->val * 2;
  return ni;
}

/* helper function checks if a value is odd */
int odd_val (void* itm) {
  int_item* i = (int_item*) itm;
  int v = i->val;
  return v % 2 != 0;
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

  /* LIST ALLOCATION & ENODATAS */

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

  printf("Get enodata... \t\t");
  my_assert((get(l,42) != NULL), ENODATA);
  /* just a test element */
  item* te = (item*) malloc(sizeof(item));
  printf("Set enodata... \t\t");
  my_assert((set(l,te,42) == 0), ENODATA);
  free(te);

  printf("Push einval...    \t");
  my_assert(((push(NULL,NULL,0)) == 0), EINVAL);

  printf("Zero length again...\t");
  my_assert(((length(l)) == 0), NO_ERROR);

  /* PUSH & APPEND */

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

  /* POP */

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

  /* CUT */

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

  /* REMOVE */

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

  /* DESTRUCTION */

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

  /* GET */

  printf("Get einval 1...\t\t");
  my_assert(((get(NULL, 3)) != NULL), EINVAL);

  printf("Get einval 2...\t\t");
  my_assert(((get(int_list, NUM_ELEMENTS)) != NULL), EINVAL);

  printf("Get einval 3...\t\t");
  my_assert(((get(int_list, -1)) != NULL), EINVAL);

  printf("Get test 1...\t\t");
  int_item* fst;
  my_assert(((fst = get(int_list, 0)) != NULL), NO_ERROR);
  printf("Get test 2...\t\t");
  int_item* lst;
  my_assert(((lst = get(int_list, NUM_ELEMENTS -1)) != NULL), NO_ERROR);
  printf("Get test 3...\t\t");
  int_item* mid;
  my_assert(((mid = get(int_list, (NUM_ELEMENTS -1) /2)) != NULL), NO_ERROR);
  /* equivalence test */
  int ceq_fst = fst->val == 0;
  int ceq_lst = lst->val == NUM_ELEMENTS -1;
  int ceq_mid = mid->val == (NUM_ELEMENTS -1) /2;
  /* information hiding test */
  free(fst);
  free(lst);
  free(mid);
  /* if the pointer is shared next instructions will cause segfault */
  fst = get(int_list, 0);
  lst = get(int_list, NUM_ELEMENTS -1);
  mid = get(int_list, (NUM_ELEMENTS -1) /2);
  printf("Get equivalence...\t");
  my_assert(ceq_fst && ceq_lst && ceq_mid, NO_ERROR);

  printf("Length after get...\t");
  my_assert(((length(int_list)) == NUM_ELEMENTS), NO_ERROR);

  /* SET */

  printf("Set einval 1...\t\t");
  my_assert(((set(int_list, NULL, 0)) == 0), EINVAL);

  fst = (int_item*) malloc(sizeof(int_item));
  lst = (int_item*) malloc(sizeof(int_item));
  mid = (int_item*) malloc(sizeof(int_item));
  if(!fst || !lst || !mid){
    fprintf(stderr, "Memory allocation failed\n");
    return 1;
  }
  fst->val = 42;
  lst->val = 42;
  mid->val = 42;

  printf("Set einval 2...\t\t");
  my_assert(((set(NULL, fst, 0)) == 0), EINVAL);

  printf("Set einval 3...\t\t");
  my_assert(((set(int_list, fst, -1)) == 0), EINVAL);

  printf("Set einval 4...\t\t");
  my_assert(((set(int_list, fst, NUM_ELEMENTS)) == 0), EINVAL);

  printf("Set test 1...\t\t");
  my_assert(((set(int_list, fst, 0)) == 0), NO_ERROR);

  printf("Set test 2...\t\t");
  my_assert(((set(int_list, lst, NUM_ELEMENTS -1)) == 0), NO_ERROR);

  printf("Set test 3...\t\t");
  my_assert(((set(int_list, fst, (NUM_ELEMENTS -1) /2)) == 0), NO_ERROR);

  /* equivalence test */
  int_item* ff, *ll, *mm;
  ff = get(int_list, 0);
  ll = get(int_list, NUM_ELEMENTS -1);
  mm = get(int_list, (NUM_ELEMENTS -1) /2);
  printf("Set equivalence...\t");
  my_assert(ff->val == 42 && ll->val == 42 && mm->val == 42, NO_ERROR);
  free(ff);
  free(ll);
  free(mm);

  printf("Length after set...\t");
  my_assert(((length(int_list)) == NUM_ELEMENTS), NO_ERROR);

  /* INDEX OF */

  printf("Index of einval 1...\t");
  my_assert(((index_of(int_list,NULL)) != -1), EINVAL);

  ff = (int_item*) malloc(sizeof(int_item));
  if(!ff){
    fprintf(stderr,"Memory allocation failed\n");
    return 1;
  }
  ff->val = NUM_ELEMENTS + 999;
  printf("Index of einval 2...\t");
  my_assert(((index_of(NULL,ff)) != -1), EINVAL);

  printf("Index of enodata 1...\t");
  my_assert(((index_of(int_list,ff)) != -1), ENODATA);


  printf("Index of enodata 2...\t");
  list_t* empty_int_list = list(cmp_int,mde_int);
  my_assert(((index_of(empty_int_list,ff)) != -1), ENODATA);

  ff->val = 46;
  printf("Index of test...\t");
  my_assert(((index_of(int_list,ff)) == 46), NO_ERROR);

  printf("Another length test...\t");
  my_assert(((length(int_list)) == NUM_ELEMENTS), NO_ERROR);

  /* MAP */

  printf("Map enodata...\t\t");
  my_assert(((map(empty_int_list,double_val)) != NULL), ENODATA);

  printf("Map einval 1...\t\t");
  my_assert(((map(NULL,double_val)) != NULL), EINVAL);

  printf("Map einval 2...\t\t");
  my_assert(((map(int_list,NULL)) != NULL), EINVAL);

  list_t* doubled_list = NULL;
  printf("Map execution...\t");
  my_assert(((doubled_list = map(int_list,double_val)) != NULL), NO_ERROR);

  int correct = 1;
  int i = 0;
  while(correct && i < NUM_ELEMENTS){
    int_item* ita = NULL, *itb = NULL;
    ita = get(int_list,i);
    itb = get(doubled_list,i);
    if(itb->val != ita->val * 2)
      correct = 0;
    free(ita);
    free(itb);
    i++;
  }
  printf("Map correctness...\t");
  my_assert(correct,NO_ERROR);

  printf("Checking length...\t");
  my_assert(((length(int_list) == length(doubled_list))), NO_ERROR);

  /* FILTER */
  printf("Filter enodata...\t");
  my_assert(((filter(empty_int_list, odd_val)) != NULL), ENODATA);

  printf("Filter einval 1...\t");
  my_assert(((filter(int_list, NULL)) != NULL), EINVAL);

  printf("Filter einval 2...\t");
  my_assert(((filter(NULL, odd_val)) != NULL), EINVAL);

  list_t* filtered_list = NULL;
  printf("Filter execution...\t");
  my_assert(((filtered_list = filter(int_list, odd_val)) != NULL), NO_ERROR);

  correct = 1;
  i = 0;
  int ln = length(filtered_list);
  while(correct && i < ln){
    int_item* it = get(filtered_list, i);
    correct = it->val % 2;
    i++;
  }
  printf("Filter correctness...\t");
  my_assert(correct, NO_ERROR);

  /* DESTRUCTION */

  printf("List destruction...\tCorrect behaviour\t-> TEST PASSED\n");
  destroy(int_list);
  
  printf("End of second test battery...\n");

  destroy(empty_int_list);
  destroy(doubled_list);

  return 0;
}
