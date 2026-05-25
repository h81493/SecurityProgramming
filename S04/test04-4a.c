#include <stdio.h>
int main( void)
{
  int a=1;
  do {
    printf("1:a = %d\n", a++);
  } while ( a < 10);
  return 0;
}
