//sec2.c
//gcc sec2.c -g  -fno-stack-protector 
#include <stdio.h>
static void vuln( void) {
  char overflowme[48];
  //%[^n] 区切り文字を\nへ。
  //https://qiita.com/Sankyuri/items/c7fb52658c45b8757b5c
  (void)scanf( "%[^\n]", overflowme);
}

int main(void) {
  int flag = 0;
  vuln();
  if(flag) 
    goto hack;
  else
    printf( "sec2 failed!\n");
  return 0;
hack:
  printf( "sec2 hacked!\n");
  return 0;
}

