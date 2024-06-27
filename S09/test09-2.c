// アセンブラで文字列表示
// gcc test09-2.c -masm=intel
#include <stdio.h>

int main( void) {
  char str[] = "Hello World!\n";  
  asm (
    ".intel_syntax noprefix;"  // I hate AT&T-style
    "mov eax, 1;"              // システムコール番号 (sys_write)
    "mov edi, 1;"              // ファイルディスクリプタ (stdout)
    "lea rsi, [%0];"           // バッファアドレス
    "mov edx, 13;"             // バイト数
    "syscall;"                 // システムコール呼び出し
    :
    : "r"(str)                   // 入力オペランド
    : "rax", "rdi", "rsi", "rdx" // 使用するレジスタ
  );
#if 0
  for(int i=0;i<sizeof(str);i++) {
    printf("%c (%p)\n",str[i],&(str[i]));
  }
#endif
  return 0;
}
