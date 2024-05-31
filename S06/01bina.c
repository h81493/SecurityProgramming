#include <stdio.h>

int main(void) {
    int j=0;
    int nishin[10];
    printf("j =");
    scanf("%d", &j);
    for(int k=1;k<=8;k++) {
        nishin[k]=j%2;
        j=(int)j/2;
    }
    for(int i=8;i>=1;i--) {
        printf("%1d",nishin[i]);
    }
    printf("\n");
}