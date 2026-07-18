#include <stdio.h>
#include <stdlib.h>  // exitを呼び出すために必要
#include <locale.h>  // setlocaleを呼び出すために必要

int main(void)
{
  FILE* fp;          /* (1)FILE構造体へのポインタを宣言 */
  char f[] = "memo.txt";

  setlocale(LC_ALL, ""); // 国や地域の属性設定
  fp = fopen(f, "r");   /* (2)ファイルを開く */
  if (fp == NULL) {
    perror("エラー");
    printf("%s ファイルを開けませんでした\n",f);
    exit(1);         // エラーなら異常終了
  } else {
    printf("ファイルを開きました\n");
  }

  fclose(fp);       /* (4)ファイルを閉じる */

  return 0;
}

