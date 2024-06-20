/******************************************
  配列
    与えられた西暦の月末の日を表示する。
******************************************/
#include <stdio.h>

int main( void) {
  int nday[] = {31,28,31,30,31,30,31,31,30,31,30,31};
  int year = 0;
  printf("西暦何年？");
  (void)scanf("%d", &year);
  printf("[%4d年]", year);
  if( (year % 4 == 0 && year % 100 != 0) || year % 400 == 0 ) {
    printf("うるう年");
    nday[1]=29;
  }
  printf("\n");
  for( int i = 0; i < 12; i++) {
    printf("%2d月%2d日 ", i+1, nday[i]);
    if( i % 4 == 3) printf("\n");
  }
  return 0;
}