#include <stdio.h>

int main(void) {
  for (int i = 1; i <= 10000; i++) {
    int sum = 0;
    // i の約数を探して和を求める。
    for (int j = 1; j < i; j++) {
      // iより小さい数について
      // それが約数ならば
      // sumに足しこむ。
      if (i % j == 0) sum=sum+j;
    }
    // 約数の和が自身に等しければ完全数
    if (sum == i) printf("%d\n", i);
  }
  return 0;
}
