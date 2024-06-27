// 構造体のポインタ渡し
#include <stdio.h>
#include <string.h>

struct st{
  int id;
  char memo[15+1];
};
static void funca(struct st s);
static void funcb(struct st* s);

int main(void) {
  struct st s;

  s.id=5;
  strcpy( s.memo, "ID = 5");
  printf("main  id = %d, memo: %s\n", s.id, s.memo);

  funca( s);// 値渡し 
  printf("main  id = %d, memo: %s\n", s.id, s.memo);

  funcb( &s);// 参照渡し
  printf("main  id = %d, memo: %s\n", s.id, s.memo);
  return 0;
}
void funca(struct st s) { //
  printf("funca id = %d, memo: %s\n", s.id, s.memo);
  s.id=8;
  strcpy(s.memo, "test");
}
void funcb(struct st* s) { //
  printf("funcb id = %d, memo: %s\n", s->id, s->memo);
  s->id=8;
  strcpy(s->memo, "test");
}
