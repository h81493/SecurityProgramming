//test10-1
#include <stdio.h>
#include <malloc.h>

int main(void) {
  int *ptr;
  //ヒープにint型を100個確保する。
  ptr = (int *)malloc(100*sizeof(int));
  //アドレスの表示
  printf("malloc: %p\n",ptr);
  //0から99までの値を書き込む。
  for(int i=0;i<100;i++) ptr[i]=i;
  //ヒープに確保したint型を200個に拡張する。
  ptr = (int *)realloc(ptr,200*sizeof(int));
  //アドレスの表示
  printf("realloc:%p\n",ptr);
  //100から199までの値を書き込む。
  for(int i=100;i<200;i++) ptr[i]=i;
  //書き込んだ値を表示する。
  for(int i=0;i<200;i++) {
    printf("%3d ",ptr[i]);
    if((i+1)%20==0) printf("\n");
  }
  printf("\n");
  free(ptr);
  return 0;
}