#include <stdio.h>

int main() {
	int n;
	int i;
	int fizz,buzz;
	scanf("%d",&n);
	i=1;
	while(i<=n) {
		fizz = (i % 3 == 0);
		buzz = (i % 5 == 0);
		if( fizz && buzz) {
			printf("FizzBuzz");
		} else if ( fizz) {
			printf("Fizz");
		} else if ( buzz) {
			printf("Buzz");
		} else {
			printf("%d", i);
		}
		i=i+1;
		printf("\n");
	}
	return 0;
}

