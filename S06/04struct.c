#include <stdio.h>

#pragma pack(1)
struct CAT { //構造体の定義
  char age;       //年齢
  int  no;        //ID
  char name[11];  //名前
};
#pragma pack()

int main( void) {
  //構造体変数の生成と初期化
  struct CAT f1 = { (char)6,1,"luna"};
  struct CAT f2 = { (char)7,2,"ten"};
  struct CAT f3 = { (char)9,3,"sora"};
  struct CAT f4 = { (char)10,4,"bell"};
  struct CAT f5 = { (char)8,5,"mocha"};
  struct CAT f6 = { (char)5,6,"kinaco"};
  struct CAT f7 = { (char)6,7,"fuku"};
  struct CAT f8 = { (char)1,8,"momo"};
  struct CAT f9 = { (char)15,9,"mugi"};

  printf("sizeof = %u\n",(unsigned)sizeof(struct CAT));
  //構造体の表示
  printf("%d %10s\n", (int)f1.age, f1.name);
  printf("%d %10s\n", (int)f2.age, f2.name);
  printf("%d %10s\n", (int)f3.age, f3.name);
  printf("%d %10s\n", (int)f4.age, f4.name);
  printf("%d %10s\n", (int)f5.age, f5.name);
  printf("%d %10s\n", (int)f6.age, f6.name);
  printf("%d %10s\n", (int)f7.age, f7.name);
  printf("%d %10s\n", (int)f8.age, f8.name);
  printf("%d %10s\n", (int)f9.age, f9.name);

  return 0;
}

