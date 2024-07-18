#include <stdio.h>
#define N     4
#define EXIT  9

int main(void) {
  char  message[N][30] = { "修理受付","納期お問い合わせ",
    "技術サポート","その他ご相談窓口"};
  int request;  //問い合わせ番号
  printf("0-%dの番号を入力してください:", N-1);
  scanf("%d", &request);
  while   (request != EXIT) {
    if    (request >= 0 && request < N) {
      printf("%sにおつなぎします\n", message[request]);
    } else    {
      printf("もう一度入力してください\n");
    }
    printf("0-%dの番号を入力してください:", N-1);
    scanf("%d", &request);
  }
  return 0;
}