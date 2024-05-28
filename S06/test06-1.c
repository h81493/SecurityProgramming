//構造体の使い方
#include <stdio.h>

struct student { //構造体の定義
  int id;
  char name[100];
};

int main( void) {
  struct student a; //構造体変数の生成
  printf("名前：");
  (void)scanf("%[^\n]",a.name);
  printf("ID:");
  (void)scanf("%d",&a.id);

  printf("ID:%04d 名前：%s\n",
    a.id,
    a.name
  );
  return 0;

}