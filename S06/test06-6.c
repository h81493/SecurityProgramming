//関数へ構造体を引数で渡す。
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
void student_print( struct STUDENT * s) {
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
/*
  printf("名前：");
  (void)scanf("%[^\n]",a.name);
  printf("ID:");
  (void)scanf("%d",&a.id);
*/
  //構造体メンバの修正
  a.id=6;
  strcpy(a.name, "test6");
  a.enrollment.year=2026;

  student_print( &a);
  return 0;
}