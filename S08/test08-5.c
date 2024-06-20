#include <stdio.h>

int hash(char *p);

int main(void) {
  char p[10+1];
  printf("パスワードを入力してください:");
  scanf("%s",p);
  printf("ハッシュ値 %d\n", hash(p));
  return 0;
}
int hash( char p[]) {
  long int h = 0;
  int ret = 0;
  for(int i = 0;p[i] != '\0'; i++) {
    h = h * 31 + p[i];
  }
  ret = h % 4093;
  return ret;
}