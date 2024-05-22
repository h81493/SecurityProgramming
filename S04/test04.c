#include <stdio.h>
int main(void)
{
  int a1=1;
  {
    int a2=2;
    printf("block2 a=%d\n",a2);
  }
  printf("block1 a=%d\n",a1);
  return(0);
}
