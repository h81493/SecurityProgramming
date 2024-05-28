#include <stdio.h>

/*@unused@*/
void pwn() {
  printf( "hacked!\n");
}

static void vuln( void) {
  char overflowme[48];
  //%[^n] 区切り文字を\nへ。
  //https://qiita.com/Sankyuri/items/c7fb52658c45b8757b5c
  (void)scanf( "%[^\n]", overflowme);
}

int main(void) {
  vuln();
  printf( "failed!\n");
  return 0;
}

