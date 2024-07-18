#include <stdio.h>
#define N 7

char *weekName[N] = { "Sunday","Monday","Tuesday","Wednesday",
  "Thursday","Friday","Saturday"};

int main(void) {
  int i,j; //添字

  for(i=0;i<N;i++) {
    printf("%d:",i);
    for(j=0; weekName[i][j] != '\0'; j++) {
//      printf("%c", weekName[i][j] );
//      printf("%c", *(weekName[i]+j) );
      printf("%c", *(weekName+i)[j] );
//      printf("%c", *(*(weekName+i)+j) );
    }
    printf("\n");
  }
  return 0;
}