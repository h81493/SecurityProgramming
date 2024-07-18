#include <stdio.h>
#define N 7

char *weekName[N] = { "Sunday","Monday","Tuesday","Wednesday",
  "Thursday","Friday","Saturday"};

int main(void) {
  char **p;
  int i; //添字
  for(p = weekName  , i=0 ; i<N; i++, p++) {
    printf("%d:%s\n",i, *p );
  }
  return 0;
}