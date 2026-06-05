#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
// RAND_MAX 0x7fffffff
#define N 100 // 並べ替える要素数
int main() {
  int i,j;
  int a[N] = {0};
  int b[N];
  struct list l = { .a=a, .b=b, .n=N};
  
  srand(1010);
  // 並べ替える配列の生成
  for( i=0; i<N;i=i+1) {
    a[i] = rand();
    b[i] = a[i];
  }
 
  // ソートプログラムの呼び出し
  sort( l);
 
  // 結果の出力
  j = 0;
  for( i=0; i<N;i=i+1) {
    if(i+1<N && b[i]<=b[i+1]) j=j+1;
    printf("%4d %12d %12d %4d\n",i,a[i],b[i],j);
  }
  if(j == N-1) {
    printf("sort Ok\n");
    return 0;
  } else {
    printf("sort NG %d\n",j);
    printf("#     #  ##### \n");
    printf("##    # #     #\n");
    printf("# #   # #      \n");
    printf("#  #  # #  ####\n");
    printf("#   # # #     #\n");
    printf("#    ## #     #\n");
    printf("#     #  ##### \n");
    return -1;
  }
}