#include <stdio.h>

int main( void)
{
  int cnt=1;
  while ( cnt<=100 ) {
    printf("%2d ", cnt);
    if ( cnt % 3 == 0 && cnt % 5 == 0) printf("Fizz,Buzz");
    else if ( cnt % 3 == 0) printf("Fizz");
    else if ( cnt % 5 == 0) printf("Buzz");
    printf("\n");
    cnt = cnt + 1;
  }
  return 0;
}
