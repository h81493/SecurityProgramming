//test10-d.c
//不正なメモリアドレスにアクセスして強制終了する。
#include <stdio.h>

int main(void) {
  int *p = NULL;
  *p = 0;

  return 0;
}