#include <stdio.h>

int main( void)
{
  int cnt=1;
  int fizz,buzz;
  while ( cnt<=100 ) {
    printf("%2d ", cnt);
    fizz = (cnt % 3 == 0);
    buzz = (cnt % 5 == 0);
    if ( fizz && buzz ) printf("Fizz,Buzz");
    else if ( fizz) printf("Fizz");
    else if ( buzz) printf("Buzz");
    printf("\n");
    cnt = cnt + 1;
  }
  printf("2 && 1 = %d \n", 2 && 1);
  printf("2 &  1 = %d \n", 2 & 1 );
  return 0;
}
