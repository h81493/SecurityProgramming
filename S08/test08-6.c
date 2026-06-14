#include <stdio.h>

void functionA(int* );

int main() {
	int a[100];

	a[2] = 2;

	printf("a = %d\n",a[2]);

	functionA(a);
	
	printf("a = %d\n",a[2]);
}

void functionA( int* array) {

	array[2] = 99;

}

