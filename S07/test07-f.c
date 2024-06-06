#include <stdio.h>

int main(void) {
  char p[2]="A:";
  printf("%d\n", 1 == 1);
  printf("%d\n",p[0] == 'A' && p[1] == ':');
  printf("%d\n",*p == 'A' && *(p + 1) == ':');

  return 0;
}