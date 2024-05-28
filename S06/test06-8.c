//課題１
#include <stdio.h>
#include <string.h>

struct LIST { //構造体の定義
  char attr[11];
  int size;
  char name[101];
};
static void list_print( struct LIST * s) {





}

int main( void) {
  //構造体変数の生成と初期化
  struct LIST f1 = { "-rw-r--r--",353,"test06-1.c"};
  struct LIST f2 = { "-rw-r--r--",386,"test06-2.c"};
  struct LIST f3 = { "-rw-r--r--",411,"test06-3.c"};
  struct LIST f4 = { "-rw-r--r--",574,"test06-4.c"};
  struct LIST f5 = { "-rw-r--r--",696,"test06-5.c"};
  struct LIST f6 = { "-rw-r--r--",776,"test06-6.c"};
  struct LIST f7 = { "-rw-r--r--",859,"test06-7.c"};
  struct LIST f8 = { "", 0, ""};
  //構造体メンバの修正



  //構造体の表示
  list_print( &f1);
  list_print( &f2);
  list_print( &f3);
  list_print( &f4);
  list_print( &f5);
  list_print( &f6);
  list_print( &f7);
  list_print( &f8);

  return 0;
}