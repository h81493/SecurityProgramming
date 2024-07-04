//test10-2
#include <stdio.h>

#include <malloc.h>

int main(void) {
  int *ptr;
  //int型配列を100個確保する。
  int a[100];
  //ヒープにint型を100個確保する。
  ptr = (int *)malloc(100*sizeof(int));
  //ヒープのアドレスの表示
  printf("malloc: %p\n",ptr);
  //配列のアドレスの表示
  printf("a     : %p\n",a);

  free(ptr);
  return 0;
}


