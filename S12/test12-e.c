#include <stdio.h>
#define N 5

//構造体の宣言
typedef struct syain{
  int number;         //社員番号
  char *name;         //氏名
  struct syain *boss; //上司
}社員;
//関数のプロトタイプ宣言
void print(社員 *pdata, int n);

int main(void) {
  社員  data[N] = {
    {1001,"田中",NULL},
    {1002,"山本",NULL},
    {1003,"渡邊",NULL},
    {1004,"鈴木",NULL},
    {1005,"佐藤",NULL},
  };
  //上司を設定する
  data[1].boss = &data[0];
  data[2].boss = &data[0];
  data[3].boss = &data[1];
  data[4].boss = &data[3];

  print(data, N);
  return 0;
}
void print(社員 *pdata, int n) {
  //pdata : 社員配列を指すポインタ
  //n : 社員の人数
  int i;   //添字
  社員 *p; //社員を指すポインタ
  //各人の組織を表示する
  for(i=0;i<n;i++,pdata++) {
    printf("%d %s",  pdata->number  ,  pdata->name  );
    for(p=  pdata->boss ; p != NULL; p =  p->boss   ) {
      printf(" - %s",   p->name  );
    }
    printf("\n");
  }
}
