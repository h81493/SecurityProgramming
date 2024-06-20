#include <stdio.h>

static void disp( char s[]); //プロトタイプ宣言

int main( void) {
  char s[10+1];
  (void)scanf("%s",s);
  disp(s);
  return 0;
}
void disp( char s[]) {
  printf("%s\n", s);
}