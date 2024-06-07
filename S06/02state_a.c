#include <stdio.h>

int main( void) {
    char c;
    int i =0;
    {
    s1:
    c=getchar();
    if(i++ == 10) goto end;
    if(c=='0') {
        printf("0");
        goto s1;
    } else {
        printf("0");
        goto s2;
    }
    s2:
    c=getchar();
    if(i++ == 10) goto end;
    if(c=='0') {
        printf("0");
        goto s1;
    } else {
        printf("1");
        goto s3;
    }
    s3:
    c=getchar();
    if(i++ == 10) goto end;
    if(c=='0') {
        printf("0");
        goto s1;
    } else {
        printf("1");
        goto s3;
    }
    }
    end:
    return 0;
}
