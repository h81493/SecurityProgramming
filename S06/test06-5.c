//構造体メンバの修正
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
  a.id=5;
  strcpy(a.name, "test5");
  a.enrollment.year=2025;

  printf("ID:%04d 名前：%s 入学：%04d年%2d月\n",
    a.id,
    a.name,
    a.enrollment.year,
    a.enrollment.month
  );
  return 0;

}