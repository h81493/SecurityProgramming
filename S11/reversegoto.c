#include <string.h>
//関数reverseを作成する。
char* reverse(char *s) {
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
  return("学籍番号");
}
