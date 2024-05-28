#include <stdio.h>

int main( void) {
  int j;
  char nishin[8];
  printf("j = ");
  (void)scanf("%d", &j);
  for(int k = 1;k <= 8;k++) {
    if ( j % 2 == 1) 
      nishin[k-1]='1';
    else
      nishin[k-1]='0';
    j =(int)(j / 2);
  }
  for(int k = 8;k >= 1;k--) {
    printf( "%c", nishin[k-1]);
  }
  printf("\n");
  return 0;
}

