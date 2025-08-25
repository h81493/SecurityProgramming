//エラーメッセージテーブルの表示 erlist.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    for (int i = 0; i < 108; i++ )
        fprintf(stderr, "%03d: %s\n", i,strerror(i));

    return EXIT_SUCCESS;
}
