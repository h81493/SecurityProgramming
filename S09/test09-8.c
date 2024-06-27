// 課題１
#include <stdio.h>

int main(void) {
  int a = 100;
  int b = 50;
  int *p;

  printf("【学籍番号】\n");
  p = &b;
  printf("*p = %d\n", *p);
  *p = 55;
  printf(" a = %d\n", a);
  printf(" b = %d\n", b);
  return 0;
}
