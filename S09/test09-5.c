// 文字列のポインタ渡し
#include <stdio.h>

static void funcc(char c);
static void funccp(char* cp);

int main(void) {
  char c;
  char cp[] = "String test.";

  c = cp[0];
  printf("c = %c, pointer c = %p\n", c, &c);// アドレスの表示
  funcc(c);// 値渡し 文字の値渡しは１文字だけ。
  printf("c = %c\n", c);

  printf("[cp] = %s, cp = %p\n", cp, cp);// アドレスの表示
  funccp(cp);// 参照渡し
  printf("cp = %s\n", cp);
  return 0;

}
void funcc(char c) { // c='S'
  c='A';   // 渡された値の書き換え
}
void funccp(char* cp) {// cp 文字列cpのポインタ
  cp[0]='B'; // 参照渡しされた参照先の値の書き換え
  printf("[cp] = %s, cp = %p\n", cp, cp);// アドレスの表示
}
