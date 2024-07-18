/*=== puzmon1: ソースコードひな形 ===*/
/*** インクルード宣言 ***/

#include <stdio.h>

/*** 列挙型宣言 ***/

/*** グローバル定数の宣言 ***/

/*** 構造体型宣言 ***/

/*** プロトタイプ宣言 ***/
int goDungeon(char *);
void doBattle(char *);
/*** 関数宣言 ***/

int main(int argc, char** argv)
{
  int win = 0;
  if(argc!=2) {
    printf("エラー:プレイヤー名を指定して起動してください。\n");
    return 1;
  }
  printf("*** Puzzle & Monsters ***\n");
  win = goDungeon(argv[1]);
  printf("***GAME CLEARED!***\n");
  printf("倒したモンスター数=%d\n",win);

  return 0;
}

/*** ユーティリティ関数宣言 ***/
int goDungeon(char *player) {
  int win = 0;
  printf("%sはダンジョンに到着した。\n", player);
  doBattle("スライム");
  win++;
  doBattle("ゴブリン");
  win++;
  doBattle("オオコウモリ");
  win++;
  doBattle("ウェアウルフ");
  win++;
  doBattle("ドラゴン");
  win++;
  printf("%sはダンジョンを制覇した！\n", player);
  return win;
}
void doBattle(char *monster) {
  printf("%sが現れた！\n", monster);
  printf("%sを倒した！\n", monster);
}
