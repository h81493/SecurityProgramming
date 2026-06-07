#include <stdio.h>
#include "sort.h"
#define DEBUG 0

/* 課題１　関数sortにプログラムを書く */
/* 引数 構造体 list を直接渡し */
void sort(struct list l) {
  int* b = l.b;
  int n   = l.n;
#ifdef DEBUG
// デバッグ用　並べ替える配列を表示する。
  {
    int i;
    for(i=0;i<n;i++) {
      printf("%d %d\n",i,b[i]);
    }
  }
#endif
// ここから並べ替えプログラムを書く

}
