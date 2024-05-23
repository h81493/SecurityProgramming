#include <stdio.h>

int main(void) {
  int i;
  (void)scanf("%d", &i);
  // i の約数を探す。
  for (int j = 1; j < i; j++) {
    if (i % j == 0)
      printf("%d\n", j);
  }
  return 0;
}
