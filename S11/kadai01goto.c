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
  char c;
  char *t;

  t=s + strlen(s)-1;
  loop1:   //gotoは使わず、
  c=*s;    //for文またはwhile文を
  *s=*t;   //使うこと。
  *t=c;
  s++;
  t--;
  if(s<t) goto loop1;
}
