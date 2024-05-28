//構造体を関数で書き換える。
#include <stdio.h>
#include <string.h>

struct DATE {
  int year;
  int month;
};
struct STUDENT { //構造体の定義
  int id;
  char name[100];
  struct DATE enrollment; 
};
static void student_edit( struct STUDENT * s) {
  //構造体メンバの修正
  s->id=6;
  strcpy(s->name, "test7");
  s->enrollment.year=2027;
/*
  printf("名前：");
  (void)scanf("%[^\n]",s->name);
  printf("ID:");
  (void)scanf("%d",&s->id);
*/
}
static void student_print( struct STUDENT * s) {
  printf("ID:%04d 名前：%s 入学：%04d年%2d月\n",
    s->id,
    s->name,
    s->enrollment.year,
    s->enrollment.month
  );
}
int main( void) {
  struct STUDENT a = {
    .name="test4",
    .id=4,
    .enrollment={2024,4}
    }; //構造体変数の生成と初期化

  student_edit( &a);
  student_print( &a);
  return 0;
}