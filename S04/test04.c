#include <stdio.h>
int main(void)
{
  int a=1;
  {
    int a=2;
    printf("block2 a=%d\n",a);
  }
  printf("block1 a=%d\n",a);
}
