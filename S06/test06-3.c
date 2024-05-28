//構造体の初期化2
#include <stdio.h>

struct STUDENT { //構造体の定義
  int id;
  char name[100];
};

int main( void) {
  struct STUDENT a = {
    .name="test3",
    .id=3
    }; //構造体変数の生成と初期化2
/*
  printf("名前：");
  (void)scanf("%[^\n]",a.name);
  printf("ID:");
  (void)scanf("%d",&a.id);
*/
  printf("ID:%04d 名前：%s\n",
    a.id,
    a.name
  );
  return 0;

}