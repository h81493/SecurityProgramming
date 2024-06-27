// 整数型のポインタ渡し
#include <stdio.h>

static void funca(int a);
static void funcap(int* ap);

int main(void) {
  int a;
  a=0;
  printf("a = %4d, ap = %p\n", a, &a);// アドレスの表示
  funca(a);// 値渡し
  printf("a = %4d\n", a);
  funcap(&a);// 参照渡し
  printf("a = %4d\n", a);
  return 0;

}
void funca(int a) { //a=0
  a=100;   // 渡された値の書き換え
}
void funcap(int* ap) {// ap 変数aのポインタ
  *ap=100; // 参照渡しされた参照先の値の書き換え
  printf("a = %4d, ap = %p\n", *ap, ap);// アドレスの表示
}
