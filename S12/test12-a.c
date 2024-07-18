#include <stdio.h>
#define N 3 //定食の種類

int main(void)
{
  char name[N][20] = 
    {"カレー定食","焼き肉定食","焼き魚定食"};
  int price[N] = {780,920,890};
  double cal[N] = {782.4,910.6,536.3};
  
  printf("               定価   カロリー\n");
  printf("%-16s %5d円 %7.1fkcal\n", name[0], price[0], cal[0]);
  printf("%-16s %5d円 %7.1fkcal\n", name[1], price[1], cal[1]);
  printf("%-16s %5d円 %7.1fkcal\n", name[2], price[2], cal[2]);

  return 0;
}