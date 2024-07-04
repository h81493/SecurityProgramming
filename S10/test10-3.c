//test10-3
#include <stdio.h>
#include <malloc.h>
#define N 4
int main(void) {
  int *ptr1;
  int *ptr2;
  //int型配列をN個確保する。
  int a[N];
  int b[N];
  //ヒープにint型をN個確保する。
  ptr1 = (int *)malloc(N*sizeof(int));
  ptr2 = (int *)malloc(N*sizeof(int));
  //ヒープのアドレスの表示
  printf("malloc1: %p\n",ptr1);
  printf("malloc2: %p\n",ptr2);
  //配列のアドレスの表示
  printf("a      : %p\n",a);
  printf("b      : %p\n",b);
  //大小比較
  printf("malloc 1 < 2 =%s\n", ptr1 < ptr2 ? "True":"False" );
  printf("       a < b =%s\n",    a < b    ? "True":"False" );
  free(ptr1);
  free(ptr2);
  return 0;
}
