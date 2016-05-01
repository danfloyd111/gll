#include <stdio.h>
#include <string.h>

#include "gll.h"

int main () {
  list_t* l = NULL;
  destroy(l);
  printf("Hi gll!\n");
  return 0;
}
