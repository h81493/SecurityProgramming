#include <stdio.h>
int main(void)
{
    int a = 1;
    {
        int b = 2;  // 内部ブロックの変数名を変更
        printf("block2 a=%d\n", b);
    }
    printf("block1 a=%d\n", a);
    return 0;  // 戻り値を追加
}
