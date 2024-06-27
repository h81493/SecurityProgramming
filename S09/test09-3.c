// インラインアセンブラの使用例
// gcc test09-3.c -masm=intel
#include <stdio.h>
#ifdef _MSC_VER
#  include <intrin.h>
#else
#  include <x86intrin.h>
#endif

int main( void) {
  unsigned long long ts0;
  unsigned long long ts1;
  unsigned long long cycle;
  char str[13+1] = "Hello World!\n";  

  // RDTSC クロックサイクル数で時間を計測する。
  // １回目
  printf("１回目\n");
  ts0 = __rdtsc(); // ts1とts0の間の処理時間を計測する。
  printf("%s", str);
  ts1 = __rdtsc();
  cycle = ts1 - ts0;
  printf("  c cycle = %8llu\n", cycle);

  ts0 = __rdtsc(); // ts1とts0の間の処理時間を計測する。
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
  ts1 = __rdtsc();
  cycle = ts1 - ts0;
  printf("asm cycle = %8llu\n", cycle);

  // ２回目
  printf("２回目\n");
  ts0 = __rdtsc(); // ts1とts0の間の処理時間を計測する。
  printf("%s", str);
  ts1 = __rdtsc();
  cycle = ts1 - ts0;
  printf("  c cycle = %8llu\n", cycle);

  ts0 = __rdtsc(); // ts1とts0の間の処理時間を計測する。
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
  ts1 = __rdtsc();
  cycle = ts1 - ts0;
  printf("asm cycle = %8llu\n", cycle);

  // CPUIDの取得
  asm (
    ".intel_syntax noprefix;"  // I hate AT&T-style
    "mov eax, 0;"             // ベンダIDの取得
    "cpuid;"                   // CPUIDの取得
    "mov dword ptr[%0], ebx;"  // EBXの値をstr[0:3]に格納
    "mov dword ptr[%1], edx;"  // EDXの値をstr[0:3]に格納
    "mov dword ptr[%2], ecx;"  // ECXの値をstr[0:3]に格納
    :"=m"(str[0]),              // 出力オペランド %0
     "=m"(str[4]),
     "=m"(str[8])
    :
    : "eax", "ebx", "edx", "ecx" // 使用するレジスタ
  );
  str[12] = '\0';
  printf("CPU ID %s\n", str);

  // Pentium FDIV bug check.
  union 
  {
    double d;
    unsigned long long int i; 
  } dividend;
  union 
  {
    double d;
    unsigned long long int i; 
  } divisor;
  union 
  {
    double d;
    unsigned long long int i; 
  } result;

  dividend.d = 4195835.0; // 分子 0x4150017ec0000000
  divisor.d = 3145727.0;  // 分母 0x4147ffff80000000

  asm (
    ".intel_syntax noprefix;" // Intel記法を使用
    "fld qword ptr [%1];"     // dividendを浮動小数点スタックにロード
    "fld qword ptr [%2];"     // divisorを浮動小数点スタックにロード
    "fdivp st(1), st;"        // スタックのトップ2つの値を除算し、結果をスタックにプッシュ
    "fstp qword ptr [%0];"    // スタックのトップの値をresultにストア
    : "=m" (result)           // 出力オペランド
    : "m" (dividend), "m" (divisor) // 入力オペランド
  );
  //printf("%.1f/%.1f = %.20f\n", dividend.d, divisor.d, result.d);
  //printf("dividend = %llx\n", dividend.i);
  //printf("divisor  = %llx\n", divisor.i);
  //printf("result   = %llx\n", result.i);
  if(result.i == 0x3ff557541c7c6b43) {
    printf("fdiv_bug : no\n");
  } else {
    printf("fdiv_bug : yes //FDIV Error ?!\n");
  }

  // 任意バイナリコードの実行
#if 0  
  printf("【警告】foof_bug がyesならばPCのリセットが必要です。\n");
  printf("noならばセグメンテーション違反で終了します。\n");
  __asm__(".byte 0xf0,0x0f,0xc7,0xc8");// mmx f00f bug check.
  // ↑のバイナリを実行すると、次の命令を実行できなくなる bugがありました。
#endif
  return 0;
}
