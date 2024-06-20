//このプログラムはエラーになります。
#include <stdio.h>

int main( void) {
  for( int i = 0; i < 3; i++) {
    //次の行はエラーになる。
    printf("%2d",{2,3,5,7,9,11,13,17}[i * sizeof(int)]);
    printf(" ");
  }
  return 0;
}
