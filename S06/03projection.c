//関係モデルの関係演算
#include <stdio.h>
#include <string.h>

struct SHOUHIN { //構造体の定義
  char no[4];     //商品番号
  char name[101]; //商品名
  int price;      //価格
  int qty;        //数量
};
static void list_print( struct SHOUHIN * s) {




}

int main( void) {
  //構造体変数の生成と初期化
  struct SHOUHIN r01 = { "A01","カメラ",13000,20};
  struct SHOUHIN r02 = { "A02","テレビ",58000,15};
  struct SHOUHIN r03 = { "B01","冷蔵庫",65000, 8};
  struct SHOUHIN r04 = { "B05","洗濯機",48000,10};
  struct SHOUHIN r05 = { "B06","乾燥機",35000,5};
  //構造体メンバの修正
  //構造体の表示
  list_print( &r01);
  list_print( &r02);
  list_print( &r03);
  list_print( &r04);
  list_print( &r05);

  return 0;
}