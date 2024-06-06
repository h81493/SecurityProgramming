#include <stdio.h>

int main( void) {
  for( int wday = 0; wday < 7; wday++) {
    for( int i = 0; i < 3; i++)
      printf("%c","日月火水木金土"[wday * 3 + i]);
      printf(" ");
  }
  return 0;
}
