#include <stdio.h>
#define N 3

int main(void)
{
	char name[N][20] = {"カレー定食","焼き肉定食","焼き魚定食"};
	int price[N] = {780,920,890};
	double cal[N] = {782.4,910.6,536.3};
	printf("              定価    カロリー\n");
	for(int i=0;i<N;i++)
	{
		printf("%-16s %5d円 %7.1fkcal\n", name[i],price[i],cal[i]);
	}
}
