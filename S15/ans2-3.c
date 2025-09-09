#include <stdio.h>
#include <string.h>
#define N 11

char buf[N];

void test(void)
{
	strcpy(buf,"サツキ");
	strcat(buf,"メイ");
}
int main(void)
{
	test();
	printf("%s\n",buf);
}


