#include <stdio.h>

struct user { //構造体テンプレート
  char name[10+1]; //名前
  int id; //ID
};
static void disp2( struct user u); //プロトタイプ宣言

int main( void) {
  struct user u;
  printf("名前=");
  (void)scanf("%s",u.name);
  printf("ID=");
  (void)scanf("%d",&(u.id));
  disp2(u);
  return 0;
}
void disp2( struct user u) {
  printf("name = %s\n", u.name);
  printf("id = %d\n", u.id);
}
