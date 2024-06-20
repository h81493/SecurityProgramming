#include <stdio.h>

int sum( int n); //プロトタイプ宣言

int main(void) {
  int n;
  printf("n = ");
  (void)scanf("%d",&n);
  printf("sum = ");
  printf(" = %d\n", sum(n));
  return 0;
}
int sum(int n) {
  int ret;
  if(n == 0) {
    ret = 0;
  } else {
    printf("%d",n);
    if(n != 1) printf(" + ");
    ret = n + sum( n - 1);
  }
  return ret;
}