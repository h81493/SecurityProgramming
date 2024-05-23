// Copyright 2024 h81493.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
/*
 リソースの解放やクリーンアップ処理が必要な場合:
関数の途中でエラーが発生した場合、goto文を使用してクリーンアップ処理を
一箇所にまとめることで、コードが簡潔になります。特に、複数のリソースを
確保し、それらを順次解放する必要がある場合に有効です。
*/

FILE *file = fopen("example.txt", "r");
if (!file) {
    goto cleanup;
}

char *buffer = malloc(1024);

	printf(" malloc() size: %zd adrs: %p %s\n", sizeof(buffer), buffer, (char *)buffer);

	strcpy(buffer, "Hello, World");
	printf(" strcpy() size: %zd adrs: %p %s\n", sizeof(buffer), buffer, (char *)buffer);


if (!buffer) {
    goto cleanup;
}

// 他の処理

cleanup:
    if (buffer) {
        free(buffer);
    }
    if (file) {
	    fclose(file);
    }
}
