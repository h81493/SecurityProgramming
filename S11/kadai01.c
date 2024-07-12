#include <stdio.h>
#include <string.h>

/* reverse:文字列sをその場所で反転する。*/
void reverse(char *s);
int main(void) {
  char msg[] = "Was it a cat I saw?";
  printf("【学籍番号】\n");//自分の学籍番号に置き換える。
  printf("%s\n",msg);
  reverse(msg);
  printf("%s\n",msg);

  return 0;
}
//関数reverseを作成する。
void reverse(char *s) {


}