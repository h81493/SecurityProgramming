#include <stdio.h>

int main(int argc, char const *argv[])
{
    int i;
    printf("argc=%d\n", argc);
    for( i=0;i<argc;i++)
    {
        printf("%d:%s\n", i, argv[i]);
    }
    return 0;
} 
