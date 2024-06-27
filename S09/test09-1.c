// スッキリ学ぶC言語P324
// gcc test09-1.c -masm=intel
#include <stdio.h>

int main() {
  int a = 10;
  int b;
  printf("sizeof int = %ld\n",sizeof(int));
  printf("a = %d, b = %d\n",a,b);
  // 変数aを変数bに写す。
  //__asm__("mov %0, %1" : "=r" (b) : "r" (a));
  asm (
    ".intel_syntax noprefix;"  // I hate AT&T-style
    "mov eax, %1;" // eax ← int a
    "mov %0, eax;" // int b ← eax
      :"=r"(b) // 出力オペランド %0
      :"r"(a)  // 入力オペランド %1
      :"eax"   // 使用するレジスタ
  );
  printf("a = %d, b = %d\n",a,b);
  return 0;
}