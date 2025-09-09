#include <stdio.h>

#define N 8

int d[N]={8,4,3,7,6,5,2,1};

void swap(int *data)
{
	int k;
	k=data[0];
	data[0]=data[1];
	data[1]=k;
}
void disp(int *data)
{
	int i;
	for(i=0;i<N;i++) {
		printf("%d ",d[i]);
	}
	printf("\n");
}
int main(void)
{
	int i,j;
	disp(d);

	for(i=0;i<N;i++) {
		for(j=0;j<N-1;j++) {
			printf("** %d **\n",j);
			if(d[j]>d[j+1]) {
				swap(d+j);
				printf("swap\n");
				disp(d);
			}
		}
	}
	disp(d);
}
				

