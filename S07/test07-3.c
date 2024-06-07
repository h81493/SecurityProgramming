/******************************************
  配列
    九九の表を作成して表示する。        
******************************************/
#include <stdio.h>
int main( void) {
  int h[9][9];
  for( int i = 0; i < 9; i++) {
    for( int j = 0; j < 9; j++) {
      h[i][j] = (i + 1)*(j + 1);
    }
  }
  for( int i = 0; i < 9; i++) {
    for( int j = 0; j < 9; j++) {
      printf( "%2d ",h[i][j]);
    }
    printf("\n");
  }
  return 0;
}