#include <stdio.h>

int main(int argc, char const *argv[])
{
    int i;
    for( i=0;i<0x100;i++)
    {
        printf("%c", *(argv[0]+i));
    }
    return 0;
} 
