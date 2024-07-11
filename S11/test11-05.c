//test11-5.c
//文字配列の配列
#include <stdio.h>
#include <string.h>

int main(void) {
  char *message[] = {
    "セキュリティプログラミング第１１回",
    "プログラム名:test11-05.c",
    "文字配列の配列で文字表示",
    0
  };
  for(char **s = message;*s!=0;++s) {
    fputs(*s, stdout);
    fputs("\n", stdout);
  }

  return 0;
}