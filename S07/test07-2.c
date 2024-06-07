/******************************************
  配列
    配列に1から10までの数字を代入して総和を表示。        
******************************************/
#include <stdio.h>
int main( void) {
  int a[10];
  int sum = 0;
  for( int i = 0; i < 10; i++) {
    a[i] = i + 1;
  }
  for( int i = 0; i < 10; i++) {
    sum = sum + a[i];
    
  }
  printf("%2d ", sum);
  printf("\n");
  return 0;
}