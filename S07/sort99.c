#include <stdlib.h>
#include "sort.h"

int comp(const void *vxp, const void *vyp) {
  int x = *(const int *) vxp;
  int y = *(const int *) vyp;
  return  x - y;
}

void sort(struct list l) {
  qsort(l.b,l.n,sizeof(l.b[0]),comp);
}
