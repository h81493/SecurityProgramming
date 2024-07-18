#include <stdio.h>
#define N 7

char *weekName[N] = { "Sunday","Monday","Tuesday","Wednesday",
  "Thursday","Friday","Saturday"};

int main(void) {
  int i; //添字
  for(i=0; i<N; i++) {
    printf("%d:%s\n",i,  weekName[i]  );
  }
  return 0;
}