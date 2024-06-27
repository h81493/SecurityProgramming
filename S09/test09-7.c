
// スタック
#include <stdio.h>

void funca(int a);
void funcb(int a);

int main(void) {
  int a=3;
  int b=1;
  printf("main  a = %d address a = %p\n", a, &a);
  printf("main  b = %d address b = %p\n", b, &b);
  funca(a);
  return 0;
}
void funca(int a) {
  int b = 5;
  printf("funca a = %d address a = %p\n", a, &a);
  printf("funca b = %d address b = %p\n", b, &b);
  a = a - 1;
  if( a == 0) {
    funca( a);
    funcb( a);
  } else if( a >= 0) funca( a);
}
void funcb(int a) {
  int b;
  printf("funcb a = %d address a = %p\n", a, &a);
  printf("funcb b = %d address b = %p\n", b, &b);
  printf("funca の変数bの値が読めた!\n");
}
